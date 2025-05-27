#pragma once

class Ranges {
public:
  virtual void add_range(int left, int right) = 0;
  virtual void remove_range(int left, int right) = 0;
  virtual bool query_range(int left, int right) = 0;
};
