#include "rranges.hpp"
#include <ng-log/logging.h>
#include <iterator>

struct StartEndLogger
{
    // Logs the interval map before and after each mutating operation.
    StartEndLogger(RRanges& instance) : instance_(instance)
    {
        LOG(INFO) << "Start: " << instance_;
    };

    ~StartEndLogger()
    {
        LOG(INFO) << "End: " << instance_;
    }

    RRanges& instance_;
};

void RRanges::add_range(int left, int right)
{
    BASE::add_range(left, right);
    StartEndLogger logger(*this);
    if (left >= right)
    {
        LOG(ERROR) << "Invalid range: [" << left << ", " << right << ")";
        return;
    }

    // lower_bound finds the first stored interval whose start is not before
    // left; any overlap with the previous interval is handled separately.
    auto it = ranges_.lower_bound(left);
    if (it == ranges_.end())
    {
        if (ranges_.empty() || ranges_.rbegin()->second < left)
        {
            ranges_[left] = right;
        }
        else if (ranges_.rbegin()->second < right)
        {
            ranges_.rbegin()->second = right;
        }
        else
        {
            return;
        }
    }
    else if (it->first == left)
    {
        // Merge every following interval that is fully covered or touches the
        // new interval.
        while (std::next(it) != ranges_.end() && std::next(it)->second < right)
        {
            ranges_.erase(std::next(it));
        }
        if (std::next(it) != ranges_.end() && std::next(it)->first < right)
        {
            right = std::next(it)->second;
            ranges_.erase(std::next(it));
        }
        if (it->second < right)
        {
            it->second = right;
        }
        else
        {
            return;
        }
    }
    else
    {
        auto prev = std::prev(it);
        if (it != ranges_.begin())
        {
            if (prev->second > right)
            {
                return;
            }
            if (prev->second > left)
            {
                left = prev->first;
                ranges_.erase(prev);
            }
        }
        if (it->first > right)
        {
            ranges_[left] = right;
        }
        else
        {
            if (it->second > right)
            {
                right = it->second;
            }
            ranges_.erase(it);
            ranges_[left] = right;
        }
    }
}

void RRanges::remove_range(int left, int right)
{
    BASE::remove_range(left, right);
    StartEndLogger logger(*this);
    if (left >= right)
    {
        LOG(ERROR) << "Invalid range: [" << left << ", " << right << ")";
        return;
    }

    // Removal either trims an existing interval, deletes covered intervals, or
    // splits one interval into two remaining pieces.
    auto it = ranges_.lower_bound(left);
    if (it == ranges_.end())
    {
        if (ranges_.empty() || ranges_.rbegin()->second <= left)
        {
            return;
        }
        int last_right = ranges_.rbegin()->second;
        ranges_.rbegin()->second = left;
        if (right < last_right)
        {
            ranges_[right] = last_right;
        }
    }
    else
    {
        while (it != ranges_.end() && it->second <= right)
        {
            it = std::next(it);
            ranges_.erase(std::prev(it));
        }
        if (it == ranges_.end() || right <= it->first)
        {
            return;
        }
        int last_right = it->second;
        ranges_.erase(it);
        ranges_[right] = last_right;
    }
}

bool RRanges::query_range(int left, int right)
{
    BASE::query_range(left, right);
    LOG(INFO) << "State: " << *this;
    if (left >= right)
    {
        LOG(ERROR) << "Invalid range: [" << left << ", " << right << ")";
        return false;
    }
    // A query is covered when either an exact-start interval contains it, or
    // the previous interval spans across the requested start.
    auto it = ranges_.lower_bound(left);
    if (it == ranges_.end())
    {
        return !(ranges_.empty() || ranges_.rbegin()->second < right);
    }
    else if (it->first == left)
    {
        return right <= it->second;
    }
    else
    {
        auto prev = std::prev(it);
        return (it != ranges_.begin() && prev->first <= left && prev->second >= right);
    }
    return false;
}

std::ostream& operator<<(std::ostream& stream, const RRanges& ranges)
{
    stream << '{';
    bool is_first = true;
    for (const auto range : ranges.ranges_)
    {
        if (!is_first)
        {
            stream << ", ";
        }
        stream << '[' << range.first << ',' << range.second << ")";
        is_first = false;
    }
    stream << '}';
    return stream;
}
