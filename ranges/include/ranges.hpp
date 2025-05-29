#pragma once

#include <ostream>

class Ranges {
  friend std::ostream &operator<<(std::ostream &stream, const Ranges &ranges);

public:
  virtual void add_range(int left, int right);
  virtual void remove_range(int left, int right);
  virtual bool query_range(int left, int right);
};

