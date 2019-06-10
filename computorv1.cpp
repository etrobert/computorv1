#include "computorv1.h"

#include "split_string.h"

using std::string;

#include <iostream>

using std::cout;
using std::endl;

#include <vector>

using std::vector;

#include <sstream>

using std::stringstream;

using nb_type = float;

static void print_polynomial(const vector<nb_type>& p) {
  for (unsigned int i(0); i < p.size(); ++i) {
    cout << p[i] << " * X^" << i;
    if (i != p.size() - 1)
      cout << " + ";
  }
  cout << endl;
}

static vector<nb_type> parse_polynomial(const string& s) {
  const auto words = split_string(s, ' ');

  vector<nb_type> coefs;

  for (unsigned int i(0); i < words.size() ; i += 4) {
    stringstream ss(words[i]);
    nb_type k;
    ss >> k;
    coefs.push_back(k);
  }
  return coefs;
}

static vector<nb_type> sub_polynomials(
  const vector<nb_type>& p1,
  const vector<nb_type>& p2) {
  const vector<nb_type>& bigger = p1.size() > p2.size() ? p1 : p2;
  const vector<nb_type>& smaller = p1.size() > p2.size() ? p2 : p1;
  vector<nb_type> r(bigger);
  for (unsigned int i(0); i < smaller.size(); ++i) {
    r[i] -= smaller[i];
  }
  return r;
}

static vector<nb_type> parse(const string& equation) {
  const auto split = split_string(equation, '=');

  auto pol1 = parse_polynomial(split[0]);
  print_polynomial(pol1);
  auto pol2 = parse_polynomial(split[1].substr(1)); // Remove the space in front
  print_polynomial(pol2);

  return sub_polynomials(pol1, pol2);
}

void computorv1(const string& equation) {
  // Parsing
  print_polynomial(parse(equation));
  // Reduction
  // Deduction of degree
}
