#include "linalg.h"

#include <algorithm>
#include <numeric>

#include <iostream>
using namespace std;

NDArray ones(Shape shape, float value) {
  NDArray a(shape);
  a.transform([=](float _) { return value; });
  return a;
}

NDArray zeros(Shape shape) {
  return ones(shape, 0.0);
}

NDArray urand(Shape shape)
{
  NDArray a = zeros(shape);
  a.transform([](float _) { return float(std::rand()) / RAND_MAX; });
  return a; 
}

NDArray eye(int rows, int cols) {
  NDArray a({rows, cols});
  
  const auto strides = a.shape().strides();
  const auto diag_stride = std::accumulate(strides.begin(), strides.end(), 0);

  for (int x=0; x<std::min(rows, cols); ++x) {
    a[x * diag_stride] = 1.0;
  }

  return a;
}


// Compute C <- A*B.
//
// A: n x m
// B: m x p
// C: n x p
//
void matmul(NDArray C, NDArray A, NDArray B) {

  check(A.ndim() == 2, "A must be a matrix");
  check(B.ndim() == 2, "B must be a matrix");
  check(C.ndim() == 2, "C must be a matrix");

  check(A.nrows() == C.nrows(), "row/colum mismatch");
  check(B.ncols() == C.ncols(), "row/colum mismatch");
  check(A.ncols() == B.nrows(), "row/colum mismatch");

  const auto n = A.nrows();
  const auto m = A.ncols();
  const auto p = C.ncols();
  
  for (int i=0; i<n; ++i) {
    for (int k=0; k<p; ++k) {
      float sum = 0.0;
      for (int j=0; j<m; ++j) {
        sum += A.at(i, j) * B.at(j, k);
      }
      C.at(i, k) = sum;
    }
  }
}

