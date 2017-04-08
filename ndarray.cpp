#include "ndarray.h"

void NDArray::describe(std::ostream &out) const {
  out << "NDArray(" << shape() << "; " << *(storage()) << ")";
}

