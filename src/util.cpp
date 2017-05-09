#include "util.h"

#include <stdexcept>

void check(bool condition, std::string msg) {
  if (!condition) {
    throw std::runtime_error(msg);
  }
}
