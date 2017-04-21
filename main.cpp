#include "buffer.h"
#include "shape.h"
#include "strides.h"
#include "ndarray.h"
#include "linalg1.h"

#include "nn/mlp.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

  NDArray a({10, 10, 4});

  a.at<char>(4, 3, 1) = 42;

  cout << a << endl;

  MultilayerPerceptron mlp(4, 1, {4, 8}, {Sigmoid, Sigmoid});

}

