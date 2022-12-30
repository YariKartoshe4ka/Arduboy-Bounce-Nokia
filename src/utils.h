#pragma once

#ifdef round
#undef round
#endif

#include <stdint.h>

template <typename T> int16_t round(T x) {
  return x > 0 ? x + .5 : x - .5;
};
