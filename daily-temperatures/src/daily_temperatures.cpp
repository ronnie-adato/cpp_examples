#include "daily_temperatures.hpp"

#include <cstddef>
#include <stack>
#include <vector>

std::vector<int> DailyTemperatures::dailyTemperatures(const std::vector<int>& temperatures)
{
    const size_t n = temperatures.size();
    std::vector<int> result(n, 0);

    std::stack<size_t> s;
    for (size_t i = 0; i < n; ++i)
    {
        while (!s.empty() && temperatures[i] > temperatures[s.top()])
        {
            const size_t prev = s.top();
            s.pop();
            result[prev] = static_cast<int>(i - prev);
        }
        s.push(i);
    }

    return result;
}
