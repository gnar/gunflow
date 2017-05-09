#ifndef NDARRAY_H
#define NDARRAY_H

#include "buffer.h"
#include "shape.h"
#include "strides.h"
//#include "slices.h"
#include "dtype.h"

#include "util.h"

#include <iosfwd>
#include <memory>
#include <stdexcept>

#include <iostream>
using namespace std;

class NDArray {
public:
  const int offset;
  const Shape shape;
  const Strides strides;
  const DType dtype;
  const std::shared_ptr<Buffer> buffer;

  NDArray(const Shape &shape)
      : offset(0), shape(shape), strides(Strides::column_major(shape)),
        dtype(f32),
        buffer(std::make_shared<Buffer>(shape.nelem * sizeof(float))) {}

  auto nrows() const { return shape.vec[0]; }
  auto ncols() const { return shape.vec[1]; }

  bool is_matrix() const { return shape.ndim == 2; }
  bool is_compact() const { return strides.is_compact(); }

  template <typename T> T *compact_begin() {
    check(is_compact(), "ndarray must be compact!");
    return reinterpret_cast<T *>(buffer->data) + offset;
  }

  template <typename T> T *compact_end() {
    check(is_compact(), "ndarray must be compact!");

    int end_idx = 0;
    for (int d = 0; d < shape.ndim; ++d) {
      end_idx += strides.vec[d] * (shape.vec[d] - 1);
    }
    end_idx += 1;

    return compact_begin<T>() + end_idx;
  }

  template <typename T> auto &index(const int linidx) const {
    return buffer->index<T>(offset + linidx);
  }

  template <typename T> auto &at(int i) const {
    return index<T>(offset + strides.linidx(i));
  }

  template <typename T> auto &at(int i, int j) const {
    return index<T>(offset + strides.linidx(i, j));
  }

  template <typename T> auto &at(int i, int j, int k) const {
    return index<T>(offset + strides.linidx(i, j, k));
  }

  void describe(std::ostream &out) const;
};

inline std::ostream &operator<<(std::ostream &out, const NDArray &a) {
  a.describe(out);
  return out;
}

template <typename T> void apply(NDArray &a, std::function<void(T &)> op) {
  if (a.is_compact()) {
    T *it = a.compact_begin<T>();

    const auto n = a.compact_end<T>() - it;
    for (auto i = 0; i < n; ++i) {
      op(it[i]);
    }
  } else {
    switch (a.shape.ndim) {
    case 1:
      for (int i = 0; i < a.shape.vec[0]; ++i) {
        op(a.at<T>(i));
      }
      break;
    case 2:
      for (int i = 0; i < a.nrows(); ++i) {
        for (int j = 0; j < a.ncols(); ++j) {
          op(a.at<T>(i, j));
        }
      }
      break;
    default:
      check(false, "not implemented");
      break;
    }
  }
}

template <typename T>
void apply(NDArray &a, NDArray &b, std::function<void(T &, T &)> op) {

  check(a.shape == b.shape, "shape mismatch");

  if (a.is_compact() && b.is_compact() && a.strides == b.strides) {
    T *it1 = a.compact_begin<T>();
    T *it2 = b.compact_begin<T>();

    const auto n1 = a.compact_end<T>() - it1;
    const auto n2 = b.compact_end<T>() - it2;
    check(n1 == n2, "bug");

    for (auto i = 0; i < n1; ++i) {
      op(it1[i], it2[i]);
    }

  } else {
    switch (a.shape.ndim) {
    case 1:
      for (int i = 0; i < a.shape.vec[0]; ++i) {
        op(a.at<T>(i), b.at<T>(i));
      }
      break;
    case 2:
      for (int i = 0; i < a.nrows(); ++i) {
        for (int j = 0; j < a.ncols(); ++j) {
          op(a.at<T>(i, j), b.at<T>(i, j));
        }
      }
      break;
    default:
      check(false, "not implemented");
      break;
    }
  }
}

#endif
