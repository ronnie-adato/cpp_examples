#include "ranges.hpp"
#include <ng-log/logging.h>

void Ranges::add_range(int left, int right)
{
    LOG(INFO) << "Add: [" << left << ", " << right << ")";
}

void Ranges::remove_range(int left, int right)
{
    LOG(INFO) << "Remove: [" << left << ", " << right << ")";
}

bool Ranges::query_range(int left, int right)
{
    LOG(INFO) << "Query: [" << left << ", " << right << ")";
    return false;
}
