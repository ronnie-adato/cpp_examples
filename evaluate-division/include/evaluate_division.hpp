#pragma once

#include <string>
#include <vector>

class EvaluateDivision
{
   public:
    // Answers division queries by composing the known equation ratios.
    std::vector<double> calcEquation(const std::vector<std::vector<std::string>>& equations,
                                     const std::vector<double>& values,
                                     const std::vector<std::vector<std::string>>& queries);
};
