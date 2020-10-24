//===-- ejercicio39.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio39
/// ===========
/// Programa que reste, sume y multiplique números complejos. (Crear la
/// estructura adecuada para representar números complejos)
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"

template<typename T>
struct Complex {
  T real;
  T imag;

  explicit Complex(T real) : real{real}, imag{0} {}

  Complex(T real, T imag) : real{real}, imag{imag} {}

  Complex operator+(const Complex<T> rhs) const {
    return Complex{real + rhs.real, imag + rhs.imag};
  }

  Complex operator-(const Complex<T> rhs) const {
    return Complex{real - rhs.real, imag - rhs.imag};
  }

  Complex operator*(const Complex<T> rhs) const {
    T new_real{(imag *rhs.imag * -1) + (real * rhs.real)};
    T new_imag{(real * rhs.imag) + (rhs.real * imag)};
    return Complex{new_real, new_imag};
  }

  bool operator==(const Complex<T> rhs) const {
    return real == rhs.real && imag == rhs.imag;
  }
};

TEST_CASE ("Test mult") {
  CHECK_EQ(Complex{3.0, 4.0} * Complex{2.0,5.0}, Complex{-14.0,23.0});
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;

  // Code here!

  return res;
}