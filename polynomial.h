#pragma once

#include <vector>
#include <string_view>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "split_string.h"
#include "math.h"

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
        if (coefs[i] < 0)
          out << "- ";
        else if (i != 0)
          out << "+ ";
        out << abs(coefs[i]) << " * X^" << i;
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

    // Returns the solutions or nothing if any number is solution
    void solve() const {
      const auto deg = degree();
      std::cout << "Polynomial degree: " << deg << std::endl;
      switch (deg) {
        case 0:
          if (coefs[0] == 0)
            std::cout << "Any number is solution." << std::endl;
          else
            std::cout << "There are no solutions." << std::endl;
          break;
        case 1:
          std::cout << "The solution is " << -coefs[0] / coefs[1] << std::endl;
          break;
        case 2:
          {
            const T d = coefs[1] * coefs[1] - 4 * coefs[0] * coefs[2];
            if (d > 0) {
              std::cout <<
                "Discriminant is strictly positive, the two solutions are:"
                << std::endl;
              const T sqrt_d = sqrt(d);
              std::cout << (-coefs[1] - sqrt_d) / (2 * coefs[2]) << std::endl;
              std::cout << (-coefs[1] + sqrt_d) / (2 * coefs[2]) << std::endl;
            } else if (d == 0)
              std::cout << "Discriminant is null, the solution is " <<
                -coefs[1] / (2 * coefs[2]) << std::endl;
            else {
              std::cout <<
                "Discriminant is strictly negative, the two solutions are:"
                << std::endl;
              const T sqrt_d = sqrt(-d);
              std::cout << (-coefs[1] / (2 * coefs[2])) <<
                " + " << sqrt_d / (2 * coefs[2]) << 'i' << std::endl;
              std::cout << (-coefs[1] / (2 * coefs[2])) <<
                " - " << sqrt_d / (2 * coefs[2]) << 'i' << std::endl;
            }
          }
          break;
        default:
          std::cout <<
            "The polynomial degree is stricly greater than 2, I can't solve."
            << std::endl;
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
