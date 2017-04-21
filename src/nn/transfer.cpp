#include "transfer.h"

#include "util.h"
#include "func/sigmoid.h"

double evaluate(TransferFunction fn, double x) {
  switch (fn) {
    case None:
      return 0;
    case Sigmoid:
      return sigmoid(x);
  }

  check(false, "not implemented");
  return 0;
}

double evaluate_derivative(TransferFunction fn, double x) {
  switch (fn) {
    case None:
      return 0;
    case Sigmoid:
      return sigmoid_derivative(x);
  }

  check(false, "not implemented");
  return 0;
}

