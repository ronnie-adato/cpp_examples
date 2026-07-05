# Decode String (LeetCode 394, Medium)

LeetCode: <https://leetcode.com/problems/decode-string/>

## Problem Description

Given an encoded string, return its decoded form. Encodings use the format `k[encoded_string]`,
where the substring inside the brackets is repeated exactly `k` times.

Inputs are valid, repeat counts are positive integers, and decoded strings do not contain digits
other than repeat counts.

## Examples

```text
Input: s = "3[a]2[bc]"
Output: "aaabcbc"
```

```text
Input: s = "3[a2[c]]"
Output: "accaccacc"
```

```text
Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
```

**Topics**: Stack, Parsing

## Build / Test (Bazel)

- Build: `bazel build //decode-string/...`
- Test: `bazel test //decode-string/tests:tests-decode-string`
