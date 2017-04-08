#include "buffer.h"

#include <ostream>

void Buffer::describe(std::ostream &out) const {
  out << "Buffer(" << size << ")";
}

