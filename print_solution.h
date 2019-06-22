#pragma once

template<typename T>
static std::string print_solution(const T& s) {
  std::ostringstream ss;
  ss << s;
  return ss.str();
}

template<>
std::string print_solution<float>(const float& s) {
  if (smath::isnan(s))
    return "(Number cannot be represented)";
  // prints -0 as 0
  else if (s == 0)
    return "0";
  else {
    std::ostringstream ss;
    ss << s;
    return ss.str();
  }
}
