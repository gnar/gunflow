#ifndef SLICES_H
#define SLICES_H

#include "slice.h"
#include <vector>
#include <string>

class Slices {
public:
  const int ndim;
  const std::vector<Slice> vec;

  Slices() : Slices({}) { }
  Slices(std::initializer_list<Slice> slices) : ndim(slices.size()), vec(slices) { }

  std::string describe() const;
};

#endif
