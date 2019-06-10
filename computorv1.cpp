#include "computorv1.h"

#include "print_vector.h"
#include "split_string.h"
#include "polynomial.h"

using std::string;

#include <iostream>
using std::cout;
using std::endl;

using nb_type = float;

static polynomial<nb_type> parse(const string& equation) {
  const auto split = split_string(equation, '=');

  polynomial<nb_type> pol1(split[0]);
  polynomial<nb_type> pol2(split[1].substr(1)); // Remove the space in front

  return pol1 - pol2;
}

void computorv1(const string& equation) {
  // Parsing
  const auto& p = parse(equation);
  // Reduction
  cout << "Reduced form: " << p << "= 0" << endl;
  // Deduction of degree
  cout << "Polynomial degree: " << p.degree() << endl;
  cout << p.solve();
}
