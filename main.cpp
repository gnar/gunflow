#include "buffer.h"
#include "shape.h"
#include "strides.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

  cout << Shape{10, 100}.ndim << endl;
  cout << Shape{10, 100}.nelem << endl;

  cout << Strides::column_major({10, 100}, 1) << endl;
}

