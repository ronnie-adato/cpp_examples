#include <gtest/gtest.h>

#include "word_break.hpp"

#include <string>
#include <unordered_set>
#include <vector>

#include <random>

namespace
{

bool wordBreakOracle(const std::string& s, const std::vector<std::string>& wordDict)
{
    std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
    std::unordered_set<size_t> lengths;
    size_t minLen = s.size();
    size_t maxLen = 0;
    for (const auto& word : dict)
    {
        lengths.insert(word.size());
        minLen = std::min(minLen, word.size());
        maxLen = std::max(maxLen, word.size());
    }

    const size_t n = s.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (size_t i = 1; i <= n; ++i)
    {
        for (const size_t len : lengths)
        {
            if (len == 0 || len > i)
            {
                continue;
            }
            const size_t j = i - len;
            if (!dp[j])
            {
                continue;
            }
            if (dict.find(s.substr(j, len)) != dict.end())
            {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

void expectSolution(const std::string& s, const std::vector<std::string>& wordDict, bool expected)
{
    WordBreak solver;
    EXPECT_EQ(solver.wordBreak(s, wordDict), expected);
}

}  // namespace

TEST(WordBreakGenericTest, EmptyString)
{
    expectSolution("", {}, true);
    expectSolution("", {"a", "abc"}, true);
}

TEST(WordBreakGenericTest, EmptyDictionary)
{
    expectSolution("a", {}, false);
    expectSolution("leetcode", {}, false);
}

TEST(WordBreakGenericTest, SingleCharacter)
{
    expectSolution("a", {"a"}, true);
    expectSolution("a", {"b"}, false);
}

TEST(WordBreakGenericTest, LeetCodeExamples)
{
    expectSolution("leetcode", {"leet", "code"}, true);
    expectSolution("applepenapple", {"apple", "pen"}, true);
    expectSolution("catsandog", {"cats", "dog", "sand", "and", "cat"}, false);
}

TEST(WordBreakGenericTest, SharedPrefixes)
{
    expectSolution("cars", {"car", "ca", "rs"}, true);
    expectSolution("catsanddog", {"cat", "cats", "and", "sand", "dog"}, true);
    expectSolution("pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"}, true);
}

TEST(WordBreakGenericTest, RepeatedAndOverlapping)
{
    expectSolution("aaaaaaa", {"aaaa", "aaa"}, true);
    expectSolution("aaaaaaa", {"aaaa", "aa"}, false);
    expectSolution("aaaa", {"a", "aa", "aaa"}, true);
}

TEST(WordBreakGenericTest, DictionaryWithDuplicates)
{
    expectSolution("abcd", {"a", "abc", "b", "cd", "cd"}, true);
    expectSolution("abcd", {"ab", "abc", "bcd"}, false);
}

TEST(WordBreakGenericTest, ExactMatchSingleWord)
{
    expectSolution("word", {"word"}, true);
    expectSolution("word", {"wor", "d"}, true);
    expectSolution("word", {"wo", "rd", "w", "ord"}, true);
}

TEST(WordBreakGenericTest, PrefixTrap)
{
    expectSolution("aaaaab", {"a", "aa", "aaa", "aaaa"}, false);
    expectSolution("aaaaab", {"a", "aa", "aaa", "aaaa", "b"}, true);
}

TEST(WordBreakGenericTest, WordsLongerThanInput)
{
    expectSolution("hi", {"hello", "world"}, false);
    expectSolution("hi", {"hello", "h", "i"}, true);
}

TEST(WordBreakGenericTest, MultiWaySplits)
{
    expectSolution("catsanddog", {"cats", "cat", "and", "sand", "dog"}, true);
    expectSolution("aaaaaa", {"a", "aa", "aaa"}, true);
}

TEST(WordBreakGenericTest, RandomizedAgainstOracle)
{
    std::mt19937 rng(0xC0FFEE);
    std::uniform_int_distribution<int> lenDist(0, 20);
    std::uniform_int_distribution<int> dictSizeDist(0, 12);
    std::uniform_int_distribution<int> wordLenDist(1, 6);
    std::uniform_int_distribution<int> charDist(0, 2);

    for (int caseIdx = 0; caseIdx < 200; ++caseIdx)
    {
        const int n = lenDist(rng);
        std::string s;
        s.reserve(static_cast<size_t>(n));
        for (int i = 0; i < n; ++i)
        {
            s.push_back(static_cast<char>('a' + charDist(rng)));
        }

        const int dictSize = dictSizeDist(rng);
        std::vector<std::string> dict;
        dict.reserve(static_cast<size_t>(dictSize));
        for (int i = 0; i < dictSize; ++i)
        {
            const int wlen = wordLenDist(rng);
            std::string word;
            word.reserve(static_cast<size_t>(wlen));
            for (int j = 0; j < wlen; ++j)
            {
                word.push_back(static_cast<char>('a' + charDist(rng)));
            }
            dict.push_back(word);
        }

        const bool expected = wordBreakOracle(s, dict);
        WordBreak solver;
        const bool actual = solver.wordBreak(s, dict);
        EXPECT_EQ(actual, expected) << "caseIdx=" << caseIdx << " s=\"" << s << "\"";
    }
}
