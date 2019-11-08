#pragma once

template<typename T>
static std::string print_any_solution(const T& s) {
  std::ostringstream ss;
  ss << s;
  return ss.str();
}

template<typename T>
std::string print_solution(const T& s) {
  return print_any_solution(s);
}

template<>
std::string print_solution<float>(const float& s) {
  if (smath::isnan(s))
    return "(Number cannot be represented)";
  // prints -0 as 0
  else if (s == 0.f)
    return "0";
  return print_any_solution(s);
}

template<>
std::string print_solution<double>(const double& s) {
  if (smath::isnan(s))
    return "(Number cannot be represented)";
  // prints -0 as 0
  else if (s == 0.)
    return "0";
  else
  return print_any_solution(s);
}
