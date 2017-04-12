#ifndef VIEW_H
#define VIEW_H

class View {

public:
  const int offset;
  const Shape shape;
  const Strides strides;
  const DType dtype = f32;

  template <typename T>
  T &data(const int linidx) {
    
  }
  

};

#endif

