#pragma once

#include <vector>
#include <string_view>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>

#include "split_string.h"
#include "print_vector.h"
#include "nullstream.h"

std::string delete_spaces_after_signs(std::string_view s);

template<typename T>
class polynomial {
  public:
    polynomial(void);
    polynomial(std::string_view s) {
      const std::string no_spaces(delete_spaces_after_signs(s));

      const auto words = split_string(no_spaces, ' ');

      for (unsigned int i(0); i < words.size() ; i += 3) {
        T k;

        // TODO double copy
        std::string str(words[i]);
        std::stringstream ss(str);
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

    std::vector<T> solve(std::ostream& vstream = nullstream::instance()) const {
      vstream << "BONJOUR";
      switch (degree()) {
        case 0:
          return std::vector<T>();
        case 1:
          return std::vector<T>{-coefs[0] / coefs[1]};
        case 2:
          {
            const T d = coefs[1] * coefs[1] - 4 * coefs[0] * coefs[2];
            if (d > 0) {
              const T sqrt_d = sqrt(d);
              return std::vector<T>{
                (-coefs[1] - sqrt_d) / (2 * coefs[2]),
                (-coefs[1] + sqrt_d) / (2 * coefs[2])
              };
            } else if (d == 0)
              return std::vector<T>{-coefs[1] / (2 * coefs[2])};
            else
              return std::vector<T>();
          }
        default:
          throw std::logic_error("Cannot compute");
      }
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
