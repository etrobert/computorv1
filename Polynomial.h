#pragma once

#include <vector>
#include <string_view>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <regex>

#include "split_string.h"
#include "smath.h"
#include "Complex.h"
#include "get_regex.h"
#include "print_solution.h"

template<typename T>
class Polynomial {
  public:
    Polynomial(void);
    Polynomial(std::string_view s) {
      parse(s);
      simplify();
    }

    T parse_number(const std::string& str) {
      T k;
      std::stringstream ss(str);
      if (!(ss >> k))
        throw std::runtime_error("Could not parse value '" + str + "'");
      return k;
    }

    static std::string regex() {
      return "(" + term_regex() + " ?)+";
    }

    static std::string term_regex() {
      return "([+-]?) ?(" + std::string(get_regex<T>()) + ") ?\\* ?X\\^([0-9]+)";
    }


    void parse(std::string_view sv) {
      const std::regex e(term_regex());
      const std::regex_iterator<std::string_view::const_iterator> riend;
      for (std::regex_iterator<std::string_view::const_iterator>
          ri(sv.begin(), sv.end(), e); ri != riend; ++ri) {
        const std::match_results<std::string_view::const_iterator> sm(*ri);
        const unsigned int power = std::atoi(sm[4].str().c_str());
        if (coefs.size() < power + 1)
          coefs.resize(power + 1);
        const T f = parse_number(sm[2].str());
        coefs[power] += (sm[1] == "-" ? -f : f);
      }
    }

    void simplify() {
      for (int i(coefs.size() - 1); i > 0; --i) {
        if (coefs[i] != 0)
          return;
        coefs.erase(coefs.begin() + i);
      }
    }

    Polynomial<T> operator-(Polynomial<T> p) const {
      Polynomial r(*this);
      if (coefs.size() < p.coefs.size())
        r.coefs.resize(p.coefs.size());
      for (unsigned int i(0); i < p.coefs.size(); ++i) {
        r.coefs[i] -= p.coefs[i];
      }
      r.simplify();
      return r;
    }

    static void print_coef(std::ostream& out, T coef, unsigned int i) {
        if (i == 0)
          out << coef;
        else {
          if (coef == -1)
            out << '-';
          else if (coef != 1)
            out << coef << " * ";

          if (i == 1)
            out << "X";
          else
            out << "X^" << i;
        }

    }

    void print(std::ostream& out) const {
      bool first(true);
      for (unsigned int i(0); i < coefs.size(); ++i) {
        if (coefs[i] == 0)
          continue;

        if (first) {
          print_coef(out, coefs[i], i);
          first = false;
        } else {
          if (coefs[i] < 0)
            out << "- ";
          else if (i != 0)
            out << "+ ";

          print_coef(out, smath::abs(coefs[i]), i);
        }

        // add a space for the next entry if it's not the last coef
        if (i != coefs.size() - 1)
          out << " ";
      }
      if (first)
        out << "0";
    }

    unsigned int degree() const {
      unsigned int deg = 0;
      for (unsigned int i(0); i < coefs.size(); ++i) {
        if (coefs[i] != 0)
          deg = i;
      }
      return deg;
    }

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
          std::cout << "The solution is:" << std::endl <<
            print_solution(-coefs[0] / coefs[1]) << std::endl;
          break;
        case 2:
          solve_2();
          break;
        default:
          std::cout <<
            "The polynomial degree is stricly greater than 2, I can't solve."
            << std::endl;
      }
    }
  private:
    void solve_2() const {
      const T d = coefs[1] * coefs[1] - 4 * coefs[0] * coefs[2];
      if (d > 0) {
        std::cout <<
          "Discriminant is strictly positive, the two solutions are:"
          << std::endl;
        const T sqrt_d = smath::sqrt(d);
        std::cout << print_solution((-coefs[1] - sqrt_d) / (2 * coefs[2]))
          << std::endl;
        std::cout << print_solution((-coefs[1] + sqrt_d) / (2 * coefs[2]))
          << std::endl;
      } else if (d == 0)
        std::cout << "Discriminant is null, the solution is " <<
          print_solution(-coefs[1] / (2 * coefs[2])) << std::endl;
      else {
        std::cout <<
          "Discriminant is strictly negative, the two solutions are:"
          << std::endl;
        const T sqrt_d = smath::sqrt(-d);
        std::cout << Complex<T>{
          -coefs[1] / (2 * coefs[2]),
            sqrt_d / (2 * coefs[2])
        } << std::endl;
        std::cout << Complex<T>{
          -coefs[1] / (2 * coefs[2]),
            -sqrt_d / (2 * coefs[2])
        } << std::endl;
      }
    }

    std::vector<T> coefs;
};

template<typename T>
std::ostream& operator<<(std::ostream &out, const Polynomial<T> &p)
{
  p.print(out);
  return out;
}
