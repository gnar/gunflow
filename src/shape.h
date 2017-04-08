#ifndef NDIM_H
#define NDIM_H

#include <iosfwd>

#include "util.h"
#include "config.h"

#include <numeric>

class Shape
{
public:
  const int ndim;
  const int nelem;
  const std::array<int, MAX_DIM> vec;

public:
  Shape() : Shape({}) {
  }

  template <typename Iter>
  Shape(Iter begin, Iter end)
    : ndim(end - begin)
    , nelem(std::accumulate(begin, end, 1, [](int a, int b) { return a*b; }))
    , vec(make_array<int, MAX_DIM>(begin, end, 1)) {
  }

  Shape(std::initializer_list<int> strides) 
    : Shape(strides.begin(), strides.end()) {
  }

  void describe(std::ostream &out) const;
};

inline std::ostream& operator<<(std::ostream& out, const Shape& d) {
  d.describe(out);
  return out;
}

#endif

