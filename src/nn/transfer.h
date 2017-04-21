#ifndef TRANSFER_H
#define TRANSFER_H

#include <cmath>

enum TransferFunction {
  None,
  Sigmoid
};

double evaluate(TransferFunction fn, double x);
double evaluate_derivative(TransferFunction fn, double x);

#endif

