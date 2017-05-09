#ifndef STRIDES_H
#define STRIDES_H

#include <iosfwd>
#include <string>

#include "config.h"
#include "util.h"

class Shape;

class Strides {
public:
  const int ndim;
  const std::array<int, MAX_DIM> vec;

  Strides() : Strides({}) {}

  template <typename Iter>
  Strides(Iter begin, Iter end)
      : ndim(end - begin), vec(make_array<int, MAX_DIM>(begin, end, 0)) {}

  Strides(std::initializer_list<int> strides)
      : Strides(strides.begin(), strides.end()) {}

  std::string describe() const;

  static Strides column_major(const Shape &shape);
  static Strides row_major(const Shape &shape);

  template <typename Iter> int linidx(Iter it, Iter end) const {
    int idx = 0;
    for (int i = 0; it != end; ++it, ++i) {
      idx += *it * vec[i];
    }
    return idx;
  }

  auto linidx(std::initializer_list<int> xs) const {
    return linidx(xs.begin(), xs.end());
  }

  auto linidx(int i) const { return linidx({i}); }
  auto linidx(int i, int j) const { return linidx({i, j}); }
  auto linidx(int i, int j, int k) const { return linidx({i, j, k}); }

  bool is_compact() const { return true; }

  bool operator==(const Strides &other) const {
    return ndim == other.ndim && vec == other.vec;
  }
};

inline std::ostream &operator<<(std::ostream &out, const Strides &d) {
  out << d.describe();
  return out;
}

#endif
