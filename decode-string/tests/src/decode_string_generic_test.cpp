#include <gtest/gtest.h>

#include "decode_string.hpp"

#include <cctype>
#include <random>
#include <string>

namespace
{

std::string DecodeReferenceImpl(const std::string &s, size_t &i);

std::string DecodeReference(const std::string &s)
{
    size_t i = 0;
    return DecodeReferenceImpl(s, i);
}

std::string DecodeReferenceImpl(const std::string &s, size_t &i)
{
    std::string out;
    while (i < s.size() && s[i] != ']')
    {
        const unsigned char uch = static_cast<unsigned char>(s[i]);
        if (std::isdigit(uch) != 0)
        {
            size_t repeat = 0;
            while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i])) != 0)
            {
                repeat = repeat * 10 + static_cast<size_t>(s[i] - '0');
                ++i;
            }
            EXPECT_LT(i, s.size());
            EXPECT_EQ(s[i], '[');
            ++i;  // skip '['
            std::string inside = DecodeReferenceImpl(s, i);
            EXPECT_LT(i, s.size());
            EXPECT_EQ(s[i], ']');
            ++i;  // skip ']'
            for (size_t k = 0; k < repeat; ++k)
            {
                out += inside;
            }
        }
        else
        {
            out += s[i];
            ++i;
        }
    }
    return out;
}

std::string RandomLetters(std::mt19937 &rng, size_t max_len)
{
    std::uniform_int_distribution<int> len_dist(0, static_cast<int>(max_len));
    std::uniform_int_distribution<int> char_dist(0, 25);
    const size_t len = static_cast<size_t>(len_dist(rng));
    std::string out;
    out.reserve(len);
    for (size_t i = 0; i < len; ++i)
    {
        out.push_back(static_cast<char>('a' + char_dist(rng)));
    }
    return out;
}

std::string RandomEncoded(std::mt19937 &rng, int depth, size_t max_atoms)
{
    std::uniform_int_distribution<int> coin(0, 99);
    std::uniform_int_distribution<int> repeat_dist(1, 20);
    std::uniform_int_distribution<int> atoms_dist(1, static_cast<int>(max_atoms));

    const int atoms = atoms_dist(rng);
    std::string out;
    for (int a = 0; a < atoms; ++a)
    {
        const int roll = coin(rng);
        if (depth > 0 && roll < 45)
        {
            const int repeat = repeat_dist(rng);
            out += std::to_string(repeat);
            out += '[';
            out += RandomEncoded(rng, depth - 1, max_atoms);
            out += ']';
        }
        else
        {
            out += RandomLetters(rng, 6);
        }
    }
    return out;
}

}  // namespace

TEST(DecodeStringGenericTest, BasicExamples)
{
    DecodeString solver;
    EXPECT_EQ(solver.decodeString("3[a]2[bc]"), "aaabcbc");
    EXPECT_EQ(solver.decodeString("3[a2[c]]"), "accaccacc");
    EXPECT_EQ(solver.decodeString("2[abc]3[cd]ef"), "abcabccdcdcdef");
}

TEST(DecodeStringGenericTest, HandlesPlainText)
{
    DecodeString solver;
    EXPECT_EQ(solver.decodeString("abc"), "abc");
    EXPECT_EQ(solver.decodeString("abc3[cd]xyz"), "abccdcdcdxyz");
}

TEST(DecodeStringGenericTest, HandlesMultiDigitRepeat)
{
    DecodeString solver;
    EXPECT_EQ(solver.decodeString("10[a]"), std::string(10, 'a'));
    EXPECT_EQ(solver.decodeString("3[a10[c]]"), "accccccccccaccccccccccacccccccccc");
}

TEST(DecodeStringGenericTest, HandlesDeepNesting)
{
    DecodeString solver;
    EXPECT_EQ(solver.decodeString("2[a2[b3[c]]]"), "abcccbcccabcccbccc");
}

TEST(DecodeStringGenericTest, RandomizedAgainstReference)
{
    DecodeString solver;
    std::mt19937 rng(1337);

    for (int t = 0; t < 300; ++t)
    {
        const std::string encoded = RandomEncoded(rng, /*depth=*/4, /*max_atoms=*/6);
        const std::string expected = DecodeReference(encoded);
        EXPECT_EQ(solver.decodeString(encoded), expected) << "encoded=\"" << encoded << "\"";
    }
}
