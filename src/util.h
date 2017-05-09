#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <array>
#include <iterator>

template <typename T, int N, typename Iter>
static std::array<T, N> make_array(Iter begin, Iter end, const T &fill_value) {
  std::array<T, N> resized;
  resized.fill(fill_value);
  std::copy(begin, end, resized.begin());
  return resized;
}

void check(bool condition, std::string msg);

#endif
