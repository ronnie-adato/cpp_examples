#include "k_closest_points_origin.hpp"

#include <ng-log/logging.h>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

std::ostream& operator<<(std::ostream& stream, const std::pair<int, size_t>& pair)
{
    stream << '{' << pair.first << ", " << pair.second << '}';
    return stream;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec)
{
    stream << "{ ";
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        stream << *it;
        if (std::distance(it, vec.end()) > 1)
        {
            stream << ", ";
        }
    }
    stream << " }";

    return stream;
}

std::vector<std::vector<int>> KClosestPointsOrigin::kClosest(const std::vector<std::vector<int>>& points, int k)
{
    LOG(INFO) << "k: " << k << " points: " << points;
    std::vector<std::pair<int, size_t>> distances(points.size());
    std::vector<std::vector<int>> results;
    results.reserve(k);
    for (size_t i = 0; i < points.size(); ++i)
    {
        distances[i] = std::make_pair(points[i][0] * points[i][0] + points[i][1] * points[i][1], i);
    }
    for (size_t i = 0; i < k && i < distances.size(); ++i)
    {
        std::make_heap(std::next(distances.rbegin(), i), distances.rend(),
                       [](const std::pair<int, size_t>& a, const std::pair<int, size_t>& b)
                       { return a.first < b.first; });
        results.push_back(points[distances[i].second]);
    }
    LOG(INFO) << "distances: " << distances;
    LOG(INFO) << "results: " << results;

    return results;
}
