#pragma once

#include <vector>

class KClosestPointsOrigin
{
   public:
    // Returns up to k points with the smallest distance from the origin.
    std::vector<std::vector<int>> kClosest(const std::vector<std::vector<int>>& points, int k);
};
