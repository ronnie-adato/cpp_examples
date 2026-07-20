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

std::ostream& operator<<(std::ostream& stream, const std::vector<std::vector<int>::iterator>& vec)
{
    stream << "{ ";
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        stream << **it;
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
    std::vector<int> distances(points.size());
    typedef std::vector<int>::iterator IT;
    std::vector<IT> distances_it(points.size());
    std::vector<std::vector<int>> results;
    results.reserve(k);
    IT it = distances.begin();
    // Store squared distances only; taking square roots would preserve the
    // ordering but costs extra work.
    for (size_t i = 0; i < points.size(); ++i)
    {
        *it = points[i][0] * points[i][0] + points[i][1] * points[i][1];
        distances_it[i] = it++;
    }
    for (size_t i = 0; i < k && i < distances_it.size(); ++i)
    {
        // Rebuild a heap over the unchosen suffix and take its closest point.
        std::make_heap(std::next(distances_it.rbegin(), i), distances_it.rend(),
                       [](const IT& a, const IT& b) { return *a < *b; });
        LOG(INFO) << "distances heap: " << distances_it;
        auto pos = std::distance(distances.begin(), distances_it[i]);
        results.push_back(points[pos]);
    }
    LOG(INFO) << "distances: " << distances;
    LOG(INFO) << "results: " << results;

    return results;
}
