#include <gtest/gtest.h>

#include "evaluate_division.hpp"

#include <cstddef>
#include <optional>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace
{

constexpr double kEps = 1e-9;

using Equations = std::vector<std::vector<std::string>>;
using Queries = std::vector<std::vector<std::string>>;

std::optional<std::vector<double>> TrySolve(EvaluateDivision& solver, const Equations& equations,
                                            const std::vector<double>& values, const Queries& queries)
{
    try
    {
        return solver.calcEquation(equations, values, queries);
    }
    catch (const std::logic_error& e)
    {
        const std::string what = e.what();
        if (what.find("Not implemented") != std::string::npos)
        {
            return std::nullopt;
        }
        throw;
    }
}

// Reference solution for test oracle: build a directed weighted graph and answer
// each query via DFS.
std::vector<double> ReferenceSolve(const Equations& equations, const std::vector<double>& values,
                                   const Queries& queries)
{
    using Adj = std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>;
    Adj graph;
    for (size_t i = 0; i < equations.size(); ++i)
    {
        const auto& e = equations[i];
        const std::string& a = e[0];
        const std::string& b = e[1];
        const double v = values[i];
        graph[a].push_back({b, v});
        graph[b].push_back({a, 1.0 / v});
    }

    auto dfs = [&](auto&& self, const std::string& src, const std::string& dst,
                   std::unordered_map<std::string, bool>& seen, double acc) -> std::optional<double>
    {
        if (src == dst)
        {
            return acc;
        }
        seen[src] = true;
        const auto it = graph.find(src);
        if (it == graph.end())
        {
            return std::nullopt;
        }
        for (const auto& [next, weight] : it->second)
        {
            if (seen[next])
            {
                continue;
            }
            if (auto got = self(self, next, dst, seen, acc * weight))
            {
                return got;
            }
        }
        return std::nullopt;
    };

    std::vector<double> out;
    out.reserve(queries.size());
    for (const auto& q : queries)
    {
        const std::string& a = q[0];
        const std::string& b = q[1];

        if (graph.find(a) == graph.end() || graph.find(b) == graph.end())
        {
            out.push_back(-1.0);
            continue;
        }

        std::unordered_map<std::string, bool> seen;
        if (auto got = dfs(dfs, a, b, seen, 1.0))
        {
            out.push_back(*got);
        }
        else
        {
            out.push_back(-1.0);
        }
    }
    return out;
}

void ExpectAnswersNear(const std::vector<double>& actual, const std::vector<double>& expected)
{
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i)
    {
        if (expected[i] < 0)
        {
            EXPECT_LT(actual[i], 0) << "i=" << i;
        }
        else
        {
            EXPECT_NEAR(actual[i], expected[i], kEps) << "i=" << i;
        }
    }
}

}  // namespace

TEST(EvaluateDivisionGenericTest, LeetCodeExample1)
{
    EvaluateDivision solver;
    const Equations equations = {{"a", "b"}, {"b", "c"}};
    const std::vector<double> values = {2.0, 3.0};
    const Queries queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};

    const auto expected = ReferenceSolve(equations, values, queries);
    auto actual = TrySolve(solver, equations, values, queries);
    if (!actual)
    {
        GTEST_SKIP() << "EvaluateDivision not implemented yet";
    }
    ExpectAnswersNear(*actual, expected);
}

TEST(EvaluateDivisionGenericTest, DisconnectedComponents)
{
    EvaluateDivision solver;
    const Equations equations = {{"a", "b"}, {"c", "d"}};
    const std::vector<double> values = {2.0, 5.0};
    const Queries queries = {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"c", "a"}, {"c", "d"}, {"d", "c"}};

    const auto expected = ReferenceSolve(equations, values, queries);
    auto actual = TrySolve(solver, equations, values, queries);
    if (!actual)
    {
        GTEST_SKIP() << "EvaluateDivision not implemented yet";
    }
    ExpectAnswersNear(*actual, expected);
}

TEST(EvaluateDivisionGenericTest, HandlesCyclesAndMultiplePaths)
{
    EvaluateDivision solver;
    const Equations equations = {{"a", "b"}, {"b", "c"}, {"a", "c"}};
    const std::vector<double> values = {2.0, 3.0, 6.0};
    const Queries queries = {{"a", "c"}, {"c", "a"}, {"b", "c"}, {"c", "b"}, {"a", "a"}};

    const auto expected = ReferenceSolve(equations, values, queries);
    auto actual = TrySolve(solver, equations, values, queries);
    if (!actual)
    {
        GTEST_SKIP() << "EvaluateDivision not implemented yet";
    }
    ExpectAnswersNear(*actual, expected);
}

TEST(EvaluateDivisionGenericTest, RandomizedAgainstReference)
{
    EvaluateDivision solver;
    std::mt19937 rng(1337);
    std::uniform_real_distribution<double> wdist(0.2, 6.0);
    std::uniform_int_distribution<int> nvars_dist(2, 18);

    for (int t = 0; t < 200; ++t)
    {
        const int n = nvars_dist(rng);
        std::vector<std::string> vars;
        vars.reserve(static_cast<size_t>(n));
        for (int i = 0; i < n; ++i)
        {
            vars.push_back("v" + std::to_string(i));
        }

        // Build a random connected graph (tree + a few extra edges).
        //
        // Note: LeetCode's problem statement assumes the input has no
        // contradictions. If we add random extra edges with arbitrary weights,
        // we can easily create inconsistent cycles (multiple paths imply
        // different ratios). This randomized test therefore constructs a hidden
        // consistent assignment for variables and derives all edge weights from
        // it.
        Equations equations;
        std::vector<double> values;

        // Hidden absolute values such that every equation is consistent:
        // equation (a/b = w) is generated as w = abs[a] / abs[b].
        std::vector<double> abs;
        abs.resize(static_cast<size_t>(n));
        abs[0] = 1.0;

        // LeetCode-style invariant for this randomized test:
        // - each equation is unique
        // - the input does not contain both (a,b) and (b,a)
        // We enforce this by de-duplicating undirected pairs.
        std::unordered_set<std::string> seen_pairs;
        auto try_add_equation = [&](const std::string& a, const std::string& b, double w)
        {
            const std::string& lo = (a < b) ? a : b;
            const std::string& hi = (a < b) ? b : a;
            std::string key;
            key.reserve(lo.size() + 1 + hi.size());
            key.append(lo);
            key.push_back('\0');
            key.append(hi);
            if (!seen_pairs.insert(key).second)
            {
                return;
            }
            equations.push_back({a, b});
            values.push_back(w);
        };

        for (int i = 1; i < n; ++i)
        {
            std::uniform_int_distribution<int> parent_dist(0, i - 1);
            const int p = parent_dist(rng);

            const double w = wdist(rng);
            try_add_equation(vars[p], vars[i], w);
            abs[static_cast<size_t>(i)] = abs[static_cast<size_t>(p)] / w;
        }
        std::uniform_int_distribution<int> extra_edges_dist(0, 2 * n);
        const int extra = extra_edges_dist(rng);
        for (int e = 0; e < extra; ++e)
        {
            std::uniform_int_distribution<int> idx_dist(0, n - 1);
            int a = idx_dist(rng);
            int b = idx_dist(rng);
            if (a == b)
            {
                continue;
            }
            // Add only consistent extra edges.
            const double w = abs[static_cast<size_t>(a)] / abs[static_cast<size_t>(b)];
            try_add_equation(vars[a], vars[b], w);
        }

        Queries queries;
        std::uniform_int_distribution<int> qcount_dist(1, 40);
        std::uniform_int_distribution<int> idx_dist(0, n - 1);
        const int qcount = qcount_dist(rng);
        queries.reserve(static_cast<size_t>(qcount));
        for (int q = 0; q < qcount; ++q)
        {
            const int a = idx_dist(rng);
            const int b = idx_dist(rng);
            queries.push_back({vars[a], vars[b]});
        }

        const auto expected = ReferenceSolve(equations, values, queries);
        auto actual = TrySolve(solver, equations, values, queries);
        if (!actual)
        {
            GTEST_SKIP() << "EvaluateDivision not implemented yet";
        }
        ExpectAnswersNear(*actual, expected);
    }
}
