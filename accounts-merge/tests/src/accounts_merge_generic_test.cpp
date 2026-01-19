#include <gtest/gtest.h>

#include "accounts_merge.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace {

std::vector<std::vector<std::string>> Normalize(std::vector<std::vector<std::string>> accounts)
{
    for (auto& account : accounts) {
        if (account.size() > 1) {
            std::sort(std::next(account.begin()), account.end());
        }
    }
    std::sort(accounts.begin(), accounts.end());
    return accounts;
}

}  // namespace

TEST(AccountsMergeGenericTest, MergesExampleFromPrompt)
{
    AccountsMerge solver;

    const std::vector<std::vector<std::string>> accounts = {
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"John", "johnnybravo@mail.com"},
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"Mary", "mary@mail.com"},
    };

    const std::vector<std::vector<std::string>> expected = {
        {"John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"},
        {"John", "johnnybravo@mail.com"},
        {"Mary", "mary@mail.com"},
    };

    EXPECT_EQ(Normalize(solver.accountsMerge(accounts)), Normalize(expected));
}

TEST(AccountsMergeGenericTest, NoMergeSameName)
{
    AccountsMerge solver;

    const std::vector<std::vector<std::string>> accounts = {
        {"Alice", "a1@mail.com"},
        {"Alice", "a2@mail.com"},
        {"Alice", "a3@mail.com"},
    };

    const std::vector<std::vector<std::string>> expected = {
        {"Alice", "a1@mail.com"},
        {"Alice", "a2@mail.com"},
        {"Alice", "a3@mail.com"},
    };

    EXPECT_EQ(Normalize(solver.accountsMerge(accounts)), Normalize(expected));
}

TEST(AccountsMergeGenericTest, ChainMerge)
{
    AccountsMerge solver;

    const std::vector<std::vector<std::string>> accounts = {
        {"Bob", "b1@mail.com", "shared@mail.com"},
        {"Bob", "shared@mail.com", "b2@mail.com"},
        {"Bob", "b3@mail.com", "b2@mail.com"},
    };

    const std::vector<std::vector<std::string>> expected = {
        {"Bob", "b1@mail.com", "b2@mail.com", "b3@mail.com", "shared@mail.com"},
    };

    EXPECT_EQ(Normalize(solver.accountsMerge(accounts)), Normalize(expected));
}

TEST(AccountsMergeGenericTest, DeduplicatesEmailsWithinAccount)
{
    AccountsMerge solver;

    const std::vector<std::vector<std::string>> accounts = {
        {"Eve", "e1@mail.com", "e1@mail.com", "e2@mail.com"},
        {"Eve", "e2@mail.com", "e3@mail.com"},
    };

    const std::vector<std::vector<std::string>> expected = {
        {"Eve", "e1@mail.com", "e2@mail.com", "e3@mail.com"},
    };

    EXPECT_EQ(Normalize(solver.accountsMerge(accounts)), Normalize(expected));
}
