#include "accounts_merge.hpp"

#include <ng-log/logging.h>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

std::ostream& operator<<(std::ostream& stream, const std::vector<std::vector<size_t>>& adj_list)
{
    for (const auto& row : adj_list)
    {
        for (size_t n : row)
        {
            stream << n << "  ";
        }
        stream << std::endl;
    }
    return stream;
}

std::vector<std::vector<std::string>> AccountsMerge::accountsMerge(
    const std::vector<std::vector<std::string>>& accounts)
{
    std::vector<std::vector<size_t>> adj_list(accounts.size());
    std::unordered_map<std::string /*email*/, size_t /*first_account*/> emails;
    for (size_t i = 0; i < accounts.size(); ++i)
    {
        for (auto it = std::next(accounts[i].begin()); it != accounts[i].end(); ++it)
        {
            auto email_it = emails.find(*it);
            if (email_it == emails.end())
            {
                emails[*it] = i;
            }
            else
            {
                adj_list[emails[*it]].push_back(i);
                adj_list[i].push_back(emails[*it]);
            }
        }
    }

    LOG(INFO) << "adj list: " << std::endl << adj_list;

    std::vector<bool> visited(accounts.size(), false);
    std::vector<size_t> representors(accounts.size(), static_cast<size_t>(-1));
    std::queue<size_t> q;
    size_t component_count = 0;
    for (size_t i = 0; i < visited.size();)
    {
        auto representor = i;
        q.push(representor);
        visited[representor] = true;
        representors[representor] = representor;
        component_count++;
        while (!q.empty())
        {
            auto account = q.front();
            q.pop();
            for (auto neighbor : adj_list[account])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    representors[neighbor] = representor;
                    q.push(neighbor);
                }
            }
        }
        for (; i < visited.size() && visited[i]; ++i);
    }

    std::vector<std::set<std::string>> merged_accounts(component_count);
    std::vector<std::vector<std::string>> result(component_count);
    std::vector<size_t> representor_to_component(accounts.size(), static_cast<size_t>(-1));
    size_t next_component = 0;

    for (size_t i = 0; i < accounts.size(); ++i)
    {
        const auto representor = representors[i];
        auto& component = representor_to_component[representor];
        if (component == static_cast<size_t>(-1))
        {
            component = next_component++;
            result[component].emplace_back(accounts[representor].front());
        }

        merged_accounts[component].insert(std::next(accounts[i].begin()), accounts[i].end());
    }

    for (size_t component = 0; component < next_component; ++component)
    {
        result[component].insert(result[component].end(), merged_accounts[component].begin(),
                                 merged_accounts[component].end());
    }

    return result;
}
