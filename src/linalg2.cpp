#include "linalg2.h"
#include "linalg1.h"

#include <algorithm>
#include <numeric>

void identity(NDArray A) {
  check(A.is_matrix(), "A must be a matrix!");
  check(A.ncols() == A.nrows(), "A must be a square matrix!");

  fill(A, 0.0);

  const auto n = A.nrows();
  for (int i=0; i<n; ++i) {
    A.at<float>(i, i) = 1.0;
  }
}

// Compute C <- A*B.
//
// A: n x m
// B: m x p
// C: n x p
//
void matmul(NDArray C, NDArray A, NDArray B) {

  check(A.dtype == f32, "A must be a f32 matrix");
  check(B.dtype == f32, "B must be a f32 matrix");
  check(C.dtype == f32, "C must be a f32 matrix");

  check(A.shape.ndim == 2, "A must be a matrix");
  check(B.shape.ndim == 2, "B must be a matrix");
  check(C.shape.ndim == 2, "C must be a matrix");

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
        sum += A.at<float>(i, j) * B.at<float>(j, k);
      }
      C.at<float>(i, k) = sum;
    }
  }
}

