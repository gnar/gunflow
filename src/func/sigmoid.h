#ifndef SIGMOID_H
#define SIGMOID_H

#include <cmath>

inline double sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }

inline double sigmoid_derivative(double x) {
  return sigmoid(x) - (1.0 - sigmoid(x));
}

#endif
