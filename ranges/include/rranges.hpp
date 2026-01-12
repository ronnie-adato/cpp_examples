#pragma once

#include "ranges.hpp"

#include <map>

class RRanges : public Ranges
{
    typedef Ranges BASE;

   public:
    void add_range(int left, int right) override;
    void remove_range(int left, int right) override;
    bool query_range(int left, int right) override;

   private:
    friend std::ostream &operator<<(std::ostream &stream, const RRanges &ranges);
    std::map<int, int> ranges_;
};

std::ostream &operator<<(std::ostream &stream, const RRanges &ranges);
