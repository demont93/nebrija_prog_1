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
    T new_real{(imag * rhs.imag * -1) + (real * rhs.real)};
    T new_imag{(real * rhs.imag) + (rhs.real * imag)};
    return Complex{new_real, new_imag};
  }

  bool operator==(const Complex<T> rhs) const {
    return real == rhs.real && imag == rhs.imag;
  }
};

struct Token {
  double value;
  char type;
};

struct TokenStream {
  bool operator>>(Token &out) {
    if (buf.empty()) {
      return false;
    } else {
      out = buf.back();
      buf.pop_back();
      return true;
    }
  }

  std::vector<Token> buf;
};

template<typename T>
TokenStream Lexer(T &input) {
  char c;
  std::vector<Token> buf{};
  while (input >> c) {
    switch (c) {
      case '-':
      case '+':
      case '*':
      case 'i': {
        buf.push_back(Token{0, c});
        break;
      }
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        input.putback(c);
        double n;
        // TODO handle err
        input >> n;
        buf.push_back(Token{n, 'n'});
        break;
      }
      default:
        throw std::runtime_error(std::string{"unidentified char: "} + c);
    }
  }
  return TokenStream{std::move(buf)};
}

TEST_CASE ("Test mult") {
    CHECK_EQ(Complex{3.0, 4.0} * Complex{2.0, 5.0}, Complex{-14.0, 23.0});
}

TEST_CASE ("Test exps") {
  std::stringstream test_input{"           "};
  DOCTEST_CHECK_NOTHROW(Lexer(test_input));
  std::stringstream test_input2{"3 + 3"};
  DOCTEST_CHECK_NOTHROW(Lexer(test_input2));
  std::stringstream test_input3{"3 -3i"};
  DOCTEST_CHECK_NOTHROW(Lexer(test_input3));
  std::stringstream test_input4{"3 -3i;"};
  DOCTEST_CHECK_THROWS(Lexer(test_input4));
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