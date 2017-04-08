#ifndef STRIDES_H
#define STRIDES_H

#include <iosfwd>

#include "util.h"
#include "config.h"

class Shape;

class Strides
{
public:
  const int ndim;
  const std::array<int, MAX_DIM> vec;

  Strides() : Strides({}) {
  }

  template <typename Iter>
  Strides(Iter begin, Iter end)
    : ndim(end - begin)
    , vec(make_array<int, MAX_DIM>(begin, end, 0)) {
  }

  Strides(std::initializer_list<int> strides) 
    : Strides(strides.begin(), strides.end()) {
  }

  void describe(std::ostream &out) const;

  static Strides column_major(const Shape &shape, int dtype_stride);
  static Strides row_major(const Shape &shape, int dtype_stride);
};

inline std::ostream& operator<<(std::ostream& out, const Strides& d) {
  d.describe(out);
  return out;
}

#endif

