#ifndef BUFFER_H
#define BUFFER_H

#include <algorithm>
#include <cstdint>
#include <iosfwd>
#include <string>

class Buffer {

public:
  const std::size_t size;
  char * const data;

  Buffer() : Buffer(0) {
  }

  Buffer(const std::size_t size) : size(size), data(new char[size]) { 
  }

  Buffer(const Buffer &other) : Buffer(other.size) {
    std::copy(other.data, other.data + other.size, data);
  }

  ~Buffer() {
    if (data) {
      delete [] data;
    }
  }

  std::string describe() const;

  template <typename T>
  auto &index(const int linidx) {
    return *(reinterpret_cast<T*>(data + linidx));
  }
};

inline std::ostream& operator<<(std::ostream& out, const Buffer& buf) {
  out << buf.describe();
  return out;
}

#endif
