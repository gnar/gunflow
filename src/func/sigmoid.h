#ifndef SIGMOID_H
#define SIGMOID_H

#include <cmath>

inline constexpr double sigmoid(double x) {
  return 1.0 / (1.0 + std::exp(-x));
}

inline constexpr double sigmoid_derivative(double x) {
  return sigmoid(x) - (1.0 - sigmoid(x));
}

#endif

