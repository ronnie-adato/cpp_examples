#include "fibonacci.hpp"
#include <ng-log/logging.h>
#include <stdexcept>

int Fibonacci::compute(int n) {
    LOG(INFO) << "compute(" << n << ") called";
    if (n < 0) throw std::invalid_argument("Negative arguments are not allowed.");
    if (memo.size() < n + 1) {
        memo.resize(n + 1, 0);
        if (n >= 1 && memo[1] == 0) {
            memo[1] = 1;
        }
    }
    if (memo[n] == 0 && n > 1) {
        LOG(INFO) << "Value for n=" << n << " not memoized, computing...";
        fib_compute(n);
    } else {
        LOG(INFO) << "Value for n=" << n << " found in memo: " << memo[n];
    }
    return memo[n];
}

void Fibonacci::fib_compute(int n) {
    LOG(INFO) << "fib_compute(" << n << ") called";
    if (memo[n] == 0 && n > 1) {
        fib_compute(n - 1);
        memo[n] = memo[n - 1] + memo[n - 2];
        LOG(INFO) << "Computed memo[" << n << "] = " << memo[n];
    }
}