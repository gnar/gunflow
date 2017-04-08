#ifndef NDARRAY_H
#define NDARRAY_H

#include "view.h"
#include "buffer.h"
#include "util.h"

#include <stdexcept>
#include <iosfwd>
#include <memory>

class NDArray
{
  const View view;
  const std::shared_ptr<Buffer> buffer;

public:
  NDArray(Shape shape) : _shape(shape), _storage(new Storage(_shape.nelem())) {
    check(_shape.is_compact(), "shape must be compact");
  }

  NDArray(Shape shape, Storage *storage) : _shape(shape), _storage(storage) {
  }

  auto ndim() const { return _shape.ndim(); }
  auto nelem() const { return _shape.nelem(); }
  auto nrows() const { return _shape.sizes()[0]; }
  auto ncols() const { return _shape.sizes()[1]; }

  auto &shape() const { return _shape; }
  auto &storage() const { return _storage; }

  auto &operator[](int linidx) const {
    return _storage->data()[linidx];
  }

  auto &at(int i) const {
    return (*this)[_shape.linidx(i)];
  }

  auto &at(int i, int j) const {
    return (*this)[_shape.linidx(i, j)];
  }

  auto &at(int i, int j, int k) const {
    return (*this)[_shape.linidx(i, j, k)];
  }

  template <typename UnaryOp>
  void transform(UnaryOp op) {
    if (shape().is_compact()) {
      transform_compact(op);
    } else {
      check(false, "not supported");
    }
  }

  void describe(std::ostream &out) const;

private:
  template <typename UnaryOp>
  void transform_compact(UnaryOp op) {
    const int ndim = shape().ndim();

    int end_idx = 0;
    for (int d=0; d<ndim; ++d) {
      end_idx += shape().strides()[d] * (shape().sizes()[d] - 1);
    }
    end_idx += 1;

    float *beg = &storage()->data()[0];
    std::transform(beg, beg + end_idx, beg, op);
  }
};

inline std::ostream& operator<<(std::ostream& out, const NDArray& a) {
  a.describe(out);
  return out;
}

#endif
