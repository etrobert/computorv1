#pragma once

#include "smath.h"
#include "print_solution.h"

template<typename T>
struct Complex {
  T a;
  T b;
};

// Prints a positive imaginary part of a complex number
template<typename T>
static void print_abs_img(std::ostream& out, T k) {
  if (k != 1)
    out << print_solution(k);
  out << 'i';
}

template<typename T>
std::ostream& operator<<(std::ostream &out, const Complex<T> &c) {
  if (c.a == 0) {
    if (c.b == 0)
      return out << '0';
    else if (c.b < 0)
      out << '-';
    print_abs_img(out, smath::abs(c.b));
  } else {
    out << print_solution(c.a);
    if (c.b == 0)
      return out;
    out << (c.b < 0 ? " - " : " + ");
    print_abs_img(out, smath::abs(c.b));
  }
  return out;
}
