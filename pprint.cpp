#include "pprint.h"

#include <iostream>

void pprint(std::ostream &out, const NDArray &a) {
  using std::endl;

  const auto shape = a.shape();
  const auto ndim = shape.ndim();

  static const std::string rows_lcr[] = {"[ ", "\n  ", " ]"};
  static const std::string cols_lcr[] = {"[ ", ", ", " ]"};

  if (ndim == 1) {

    const int rows = shape.sizes()[0];

    for (int i=0; i<rows; ++i) {
      if (i == 0) out << rows_lcr[0];

      out << a.at(i);
 
      if (i < rows-1) out << rows_lcr[1];
      if (i == rows-1) out << rows_lcr[2];
    }
    
  } else if (ndim == 2) {

    const int rows = shape.sizes()[0];
    const int cols = shape.sizes()[1];

    for (int i=0; i<rows; ++i) {
      if (i == 0) out << rows_lcr[0];

      for (int j=0; j<cols; ++j) {
        if (j == 0) out << cols_lcr[0];
        out << a.at(i, j);
        if (j < cols-1) out << cols_lcr[1];
        if (j == cols-1) out << cols_lcr[2];
      }
 
      if (i < rows-1) out << rows_lcr[1];
      if (i == rows-1) out << rows_lcr[2];
    }

  } else {
    out << "(not implemented)" << endl;
  }
}

