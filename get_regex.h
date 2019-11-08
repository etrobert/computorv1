#pragma once

template<typename T>
std::string_view get_regex();

template<>
std::string_view get_regex<int>() {
  return "[0-9]+";
}

template<>
std::string_view get_regex<float>() {
  return "[0-9]+(\\.[0-9]+)?";
}

template<>
std::string_view get_regex<double>() {
  return "[0-9]+(\\.[0-9]+)?";
}

