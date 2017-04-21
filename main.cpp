#include "buffer.h"
#include "shape.h"
#include "strides.h"
#include "ndarray.h"

#include "linalg1.h"
#include "linalg2.h"
#include "pprint.h"

#include "nn/mlp.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

  NDArray a({10, 20});
  NDArray b({20, 10});
  NDArray c({10, 10});

  normal(a, 0.0, 1.0);
  normal(b, 0.0, 1.0);
  matmul(c, a, b);

  pprint(cout, c);
}

