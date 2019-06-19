#pragma once

namespace smath {
  template<typename T>
  T pow(T x, unsigned int n) {
    T r(1);
    while (n-- > 0)
      r *= x;
    return r;
  }

  unsigned int log(unsigned int base, unsigned int x);

  unsigned int rough_sqrt(unsigned int x);

  template<typename T>
  double sqrt_r(T s, double x, unsigned int iter) {
    if (iter == 0)
      return x;
    return sqrt_r(s, (x + s / x) / 2, iter - 1);
  }

  // s should be positive
  template<typename T>
  double sqrt(T s, unsigned int iter = 10) {
    return sqrt_r(s, static_cast<double>(rough_sqrt(s)), iter);
  }

  template<typename T>
  T abs(T n) {
    if (n == 0)
      return 0;
    return (n > 0) ? n : -n;
  }
}
