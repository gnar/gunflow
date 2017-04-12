#ifndef NDARRAY_H
#define NDARRAY_H

#include "shape.h"
#include "strides.h"
#include "buffer.h"
//#include "slices.h"
#include "dtype.h"

#include "util.h"

#include <stdexcept>
#include <iosfwd>
#include <memory>

#include <iostream>
using namespace std;

class NDArray
{
public:
  const int offset;
  const Shape shape;
  const Strides strides;
  const DType dtype;
  const std::shared_ptr<Buffer> buffer;

  NDArray(const Shape &shape) 
    : offset(0)
    , shape(shape)
    , strides(Strides::column_major(shape, sizeof(float)))
    , dtype(f32) 
    , buffer(std::make_shared<Buffer>(shape.nelem * sizeof(float))) {
  }

  auto nrows() const { return shape.vec[0]; }
  auto ncols() const { return shape.vec[1]; }

  template <typename T>
  auto &index(const int linidx) const {
    return buffer->index<T>(offset + linidx);
  }

  template <typename T>
  auto &at(int i) const {
    return index<T>(offset + strides.linidx(i));
  }

  template <typename T>
  auto &at(int i, int j) const {
    return index<T>(offset + strides.linidx(i, j));
  }

  template <typename T>
  auto &at(int i, int j, int k) const {
    cout << offset + strides.linidx(i, j, k) << endl;
    return index<T>(offset + strides.linidx(i, j, k));
  }

  /*template <typename UnaryOp>
  void transform(UnaryOp op) {
    if (shape().is_compact()) {
      transform_compact(op);
    } else {
      check(false, "not supported");
    }
  }*/

  void describe(std::ostream &out) const;

private:
  /*template <typename UnaryOp>
  void transform_compact(UnaryOp op) {
    const int ndim = shape().ndim();

    int end_idx = 0;
    for (int d=0; d<ndim; ++d) {
      end_idx += shape().strides()[d] * (shape().sizes()[d] - 1);
    }
    end_idx += 1;

    float *beg = &storage()->data()[0];
    std::transform(beg, beg + end_idx, beg, op);
  }*/
};

inline std::ostream& operator<<(std::ostream& out, const NDArray& a) {
  a.describe(out);
  return out;
}

#endif
