#ifndef NDIM_H
#define NDIM_H

#include <iosfwd>
#include <numeric>
#include <string>

#include "util.h"
#include "config.h"


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

  std::string describe() const;
};

inline std::ostream& operator<<(std::ostream& out, const Shape& shape) {
  out << shape.describe();
  return out;
}

#endif

