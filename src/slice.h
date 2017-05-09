#ifndef SLICE_H
#define SLICE_H

#include "config.h"

#include <climits>
#include <string>

class Slice {
public:
  const int x0;
  const int x1;
  const int step;

  Slice(int x0, int x1, int step = 1) : x0(x0), x1(x1), step(step) {}
  Slice(const Slice &other) = default;
  ~Slice() = default;

  std::string describe() const;
};

inline std::ostream &operator<<(std::ostream &out, const Slice &slice) {
  out << slice.describe();
  return out;
}

#endif
