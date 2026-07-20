#pragma once

#include <vector>

class Fibonacci
{
   public:
    // Computes the nth Fibonacci number, memoizing values across calls.
    int compute(int n);

   private:
    // Fills memo[n] recursively after ensuring smaller values are available.
    void fib_compute(int n);
    std::vector<int> memo;
};
