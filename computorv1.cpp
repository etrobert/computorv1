#include "computorv1.h"

#include "split_string.h"
#include "Polynomial.h"

#include <iostream>
using std::cout;
using std::endl;

using std::string_view;

using nb_type = float;

static Polynomial<nb_type> parse(string_view equation) {
  std::regex reg(Polynomial<nb_type>::regex() + " = " + Polynomial<nb_type>::regex());
  if (!regex_match(equation.begin(), equation.end(), reg))
    throw std::runtime_error("The equation format is not valid");
  const auto split = split_string(equation, '=');

  Polynomial<nb_type> pol1(split[0]);
  Polynomial<nb_type> pol2(split[1].substr(1)); // Remove the space in front

  return pol1 - pol2;
}

void computorv1(string_view equation) {
  try {
    // Parsing
    const auto p = parse(equation);
    // Reduction
    cout << "Reduced form: " << p << " = 0" << endl;
    // Deduction of degree
    p.solve();
  } catch (std::runtime_error& e) {
    cout << "And error occured during parsing : " << e.what() << endl;
  }
}
