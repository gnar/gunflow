#include "linalg1.h"

#include <algorithm>
#include <numeric>
#include <random>

static std::mt19937_64 engine;

void fill(NDArray A, float val) {
  apply<float>(A, [=](float &x) { x = val; });
}

void scale(NDArray A, float s) {
  apply<float>(A, [=](float &x) { x *= s; });
}

// A <- A + B
void add(NDArray A, NDArray B) {
  apply<float>(A, B, [](float &a, float &b) { a += b; });
}

// A <- A - B
void sub(NDArray A, NDArray B) {
  apply<float>(A, B, [](float &a, float &b) { a -= b; });
}

// A <- p(normal(mean, stddev))
void normal(NDArray A, float mean, float stddev) {
  std::normal_distribution<float> dist(mean, stddev);
  apply<float>(A, [&](float &a) { a = dist(engine); });
}
