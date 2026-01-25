#pragma once

#include <string>
#include <vector>

class EvaluateDivision
{
   public:
    std::vector<double> calcEquation(const std::vector<std::vector<std::string>> &equations,
                                     const std::vector<double> &values,
                                     const std::vector<std::vector<std::string>> &queries);
};
