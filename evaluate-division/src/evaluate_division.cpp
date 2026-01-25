#include "evaluate_division.hpp"

#include <ng-log/logging.h>
#include <algorithm>
#include <cstddef>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

std::ostream& operator<<(std::ostream& stream, const std::vector<std::vector<std::string>>& expressions)
{
    for (const auto& expression : expressions)
    {
        stream << expression[0] << '/' << expression[1] << std::endl;
    }
    return stream;
}

std::vector<double> EvaluateDivision::calcEquation(const std::vector<std::vector<std::string>>& equations,
                                                   const std::vector<double>& values,
                                                   const std::vector<std::vector<std::string>>& queries)
{
    LOG(INFO) << "EvaluateDivision::calcEquation"
              << " equations=" << equations.size() << " values=" << values.size() << " queries=" << queries.size();

    LOG(INFO) << "equations: " << std::endl << equations;
    LOG(INFO) << "queries: " << std::endl << queries;

    std::unordered_map<std::string, std::unordered_map<std::string, double>> weighted_adj_list;
    for (size_t i = 0; i < equations.size(); ++i)
    {
        std::vector<std::string> equation = equations[i];
        LOG(INFO) << "add edge " << equation.front() << "->" << equation.back() << " w=" << values[i];
        LOG(INFO) << "add edge " << equation.back() << "->" << equation.front() << " w=" << (1 / values[i]);
        weighted_adj_list[equation.front()][equation.back()] = values[i];
        weighted_adj_list[equation.back()][equation.front()] = 1 / values[i];
    }

    std::vector<double> results(queries.size(), -1.0);
    for (size_t j = 0; j < queries.size(); ++j)
    {
        std::vector<std::string> query = queries[j];
        LOG(INFO) << "query[" << j << "] " << query.front() << "/" << query.back();
        if (weighted_adj_list.find(query.front()) == weighted_adj_list.end() ||
            weighted_adj_list.find(query.back()) == weighted_adj_list.end())
        {
            LOG(INFO) << "unknown variable in query; returning -1";
            results[j] = -1.0;
        }
        else if (query.front() == query.back())
        {
            LOG(INFO) << "identity query; returning 1";
            results[j] = 1.0;
        }
        else if (weighted_adj_list[query.front()].find(query.back()) != weighted_adj_list[query.front()].end())
        {
            LOG(INFO) << "direct edge found; using cached ratio";
            results[j] = weighted_adj_list[query.front()][query.back()];
        }
        else
        {
            // bfs
            LOG(INFO) << "no direct edge; running bfs expansion from " << query.front();
            std::unordered_set<std::string> unvisited;
            for (auto [numerator, _] : weighted_adj_list)
            {
                unvisited.insert(numerator);
            }
            std::queue<std::pair<std::string, std::string>> q;
            for (auto [denominator, _] : weighted_adj_list[query.front()])
            {
                q.push(std::make_pair(query.front(), denominator));
            }
            unvisited.erase(query.front());
            while (!q.empty())
            {
                auto [numerator, denominator] = q.front();
                q.pop();
                for (auto [new_denominator, _] : weighted_adj_list[denominator])
                {
                    if (unvisited.find(new_denominator) != unvisited.end())
                    {
                        q.push(std::make_pair(denominator, new_denominator));
                        weighted_adj_list[query.front()][new_denominator] =
                            weighted_adj_list[query.front()][denominator] *
                            weighted_adj_list[denominator][new_denominator];
                        weighted_adj_list[new_denominator][query.front()] =
                            1 / weighted_adj_list[query.front()][new_denominator];
                        unvisited.erase(new_denominator);
                        if (new_denominator == query.back())
                        {
                            results[j] = weighted_adj_list[query.front()][query.back()];
                        }
                        LOG(INFO) << "discovered " << query.front() << "/" << new_denominator << "="
                                  << weighted_adj_list[query.front()][new_denominator];
                    }
                }
            }
        }
    }

    LOG(INFO) << "Results: ";
    for (auto r : results)
    {
        LOG(INFO) << r << ' ';
    }

    LOG(INFO) << "EvaluateDivision::calcEquation done";
    return results;
}
