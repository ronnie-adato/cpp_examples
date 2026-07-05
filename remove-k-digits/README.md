# Remove K Digits (LeetCode 402, Medium)

LeetCode: <https://leetcode.com/problems/remove-k-digits/>

## Problem Description

Given a non-negative integer represented as a string `num` and an integer `k`, remove exactly `k`
digits so that the remaining number is as small as possible.

Return the result as a string. The returned value should not contain leading zeroes unless the
answer is exactly `0`.

## Examples

```text
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the digits 4, 3, and 2 to form the smallest number.
```

```text
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1; the result is 200 after trimming leading zeroes.
```

```text
Input: num = "10", k = 2
Output: "0"
Explanation: All digits are removed.
```

**Topics**: Greedy, Monotonic Stack
