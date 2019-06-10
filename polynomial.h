#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "split_string.h"

void delete_spaces_after_signs(std::string& s);

template<typename T>
class polynomial {
  public:
    polynomial(void);
    polynomial(const std::string& s) {
      std::string no_spaces(s);
      delete_spaces_after_signs(no_spaces);

      const auto words = split_string(no_spaces, ' ');

      for (unsigned int i(0); i < words.size() ; i += 3) {
        std::stringstream ss(words[i]);
        T k;
        ss >> k;
        coefs.push_back(k);
      }
    }

    polynomial<T> operator-(polynomial<T> p) const {
      const polynomial& bigger = this->coefs.size() > p.coefs.size() ? *this : p;
      const polynomial& smaller = this->coefs.size() > p.coefs.size() ? p : *this;
      polynomial r(bigger);
      for (unsigned int i(0); i < smaller.coefs.size(); ++i) {
        r.coefs[i] -= smaller.coefs[i];
      }
      return r;
    }

    void print(std::ostream& out) const {
      for (unsigned int i(0); i < coefs.size(); ++i) {
        out << std::showpos << coefs[i] << " * X^" << i;
        if (i != coefs.size() + 1)
          out << " ";
      }
    }

    unsigned int degree() const {
      unsigned int deg = 0;
      for (unsigned int i(0); i < coefs.size(); ++i) {
        if (coefs[i] != 0)
          deg = i;
      }
      return deg;
    }
  private:
    std::vector<T> coefs;
};

template<typename T>
std::ostream& operator<<(std::ostream &out, const polynomial<T> &p)
{
  p.print(out);
  return out;
}
