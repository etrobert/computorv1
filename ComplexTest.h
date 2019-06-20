#pragma once

#include "Complex.h"

template<typename T>
void test_stream(Complex<T> c, std::string s) {
  std::stringstream ss;
  ss << c;
  EXPECT_EQ(ss.str(), s);
}

TEST(ComplexTest, StreamOperator) {
  test_stream(Complex<int>{1, 2}, "1 + 2i");
  test_stream(Complex<int>{1, -2}, "1 - 2i");
  test_stream(Complex<int>{2, 0}, "2");
  test_stream(Complex<int>{0, 2}, "2i");
  test_stream(Complex<int>{0, -2}, "-2i");
  test_stream(Complex<int>{0, 1}, "i");
  test_stream(Complex<int>{0, -1}, "-i");
  test_stream(Complex<int>{0, 0}, "0");
}
