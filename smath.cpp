#include "smath.h"

namespace smath {
  unsigned int log(unsigned int base, unsigned int x) {
    unsigned int l(0);
    while ((x /= base) != 0)
      ++l;
    return l;
  }

  unsigned int rough_sqrt(unsigned int x) {
    const unsigned int n = log(100, x);
    const unsigned int a = x / pow(100, n);
    return (a < 10 ? 2 : 6) * pow(10, n);
  }

  bool isnan(float n) {
    return n != n;
  }
}
