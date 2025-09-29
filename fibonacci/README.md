# Fibonacci Problem

Implement a function that returns the nth Fibonacci number. To optimize performance, use memoization to cache previously computed results and avoid redundant calculations.

## Requirements
- Input: An integer n (n >= 0)
- Output: The nth Fibonacci number
- Optimization: Use memoization (e.g., a map or array) to store and reuse results

## Example
```
fib(0) -> 0
fib(1) -> 1
fib(5) -> 5
fib(10) -> 55
```

## Notes
- The Fibonacci sequence is defined as:
  - fib(0) = 0
  - fib(1) = 1
  - fib(n) = fib(n-1) + fib(n-2) for n > 1
- Memoization greatly improves performance for large n
