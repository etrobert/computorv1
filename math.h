#pragma once

template<typename T>
T pow(T x, unsigned int n) {
  T r(1);
  while (n-- > 0)
    r *= x;
  return r;
}

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

template<typename T>
double sqrt_r(T s, double x, unsigned int iter) {
  if (iter == 0)
    return x;
  return sqrt_r(s, (x + s / x) / 2, iter - 1);
}

// x should be positive
template<typename T>
double sqrt(T s, unsigned int iter = 10) {
  return sqrt_r(s, static_cast<double>(rough_sqrt(s)), iter);
}
