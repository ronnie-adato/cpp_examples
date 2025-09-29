#pragma once

#include <vector>

class Fibonacci {
public:
    int compute(int n);
private:
    void fib_compute(int n);
    std::vector<int> memo;
};
