#pragma once

#include "ranges.hpp"

#include <map>

class RRanges : public Ranges {
public:
  void add_range(int left, int right) override;
  void remove_range(int left, int right) override;
  bool query_range(int left, int right) override;

private:
  std::map<int, int> ranges_;
};
