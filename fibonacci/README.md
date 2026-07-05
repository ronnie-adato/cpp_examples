# Fibonacci Number (LeetCode 509, Easy)

LeetCode: <https://leetcode.com/problems/fibonacci-number/>

## Problem Description

Implement a function that returns the nth Fibonacci number.
To optimize performance, use memoization to cache previously computed results and avoid redundant
calculations.

## Requirements

- Input: An integer n (n >= 0)
- Output: The nth Fibonacci number
- Optimization: Use memoization (e.g., a map or array) to store and reuse results

## Examples

```text
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
```

```text
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
```

```text
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
```

## Notes

- The Fibonacci sequence is defined as:
  - fib(0) = 0
  - fib(1) = 1
  - fib(n) = fib(n-1) + fib(n-2) for n > 1
- Memoization greatly improves performance for large n

## Build / Test (Bazel)

- Build: `bazel build //fibonacci/...`
- Test: `bazel test //fibonacci/tests:tests-fibonacci`
