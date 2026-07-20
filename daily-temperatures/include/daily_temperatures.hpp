#pragma once

#include <vector>

class DailyTemperatures
{
   public:
    // For each day, returns how many days pass before a warmer temperature.
    std::vector<int> dailyTemperatures(const std::vector<int>& temperatures);
};
