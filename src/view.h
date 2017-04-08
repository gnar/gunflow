#ifndef VIEW_H
#define VIEW_H

enum DType {
  i32, f32
};

class View {

public:
  const int offset;
  const Shape shape;
  const Strides strides;
  const DType dtype = f32;

  template <typename T>
  T &data(const int linidx) {
    
  }
  

  auto linidx(int i) const {
    return offset + strides[0] * i;
  }

  auto linidx(int i, int j) const {
    return offset + strides[0] * i + strides[1] * j;
  }

  auto linidx(int i, int j, int k) const {
    return offset + strides[0] * i + strides[1] * j + strides[2] * k;
  }

  auto linidx(const int * const indices) const {
    auto idx = 0;
    for (auto d = 0; d < _ndim; ++d) {
      idx += indices[d] * strides[d];
    }
    return idx;
  }

  bool is_compact() const {
    return true;
  }
};

#endif

