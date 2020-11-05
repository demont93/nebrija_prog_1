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
#include "user_io.h"

template<typename T>
struct Complex {
  T real{0};
  T imag{0};

  explicit Complex() = default;

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
  bool operator==(const Token &rhs) const {
    return value == rhs.value && type == rhs.type;
  }


  double value{};
  char type{};
};

struct TokenStream {
  [[nodiscard]] bool operator>>(Token &out) {
    if (current_elem >= buf.size()) {
      return false;
    } else {
      out = buf[current_elem++];
      return true;
    }
  }

  void putback(Token &tok) {
    if (current_elem == 0 || tok != buf[current_elem - 1])
      throw std::runtime_error("cant putback to empty token stream");
    else
      --current_elem;
  }

  std::vector<Token> buf;
  size_t current_elem{0};
};

template<typename T>
TokenStream Lexer(T &input) {
  char c;
  std::vector<Token> buf{};
  while (input >> c) {
    switch (c) {
      case '-':case '+':case '*':case 'i': {
        buf.push_back(Token{0, c});
        break;
      }
      case '0':case '1':case '2':case '3':case '4':
      case '5':case '6':case '7':case '8':case '9': {
        input.putback(c);
        double n;
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

// Parse tree:
// Expr    -> Term (- | +) Expr | Term
// Term    -> Complex * Term | Complex
// Complex -> Number Number i
// Number -> (- | +) digits | digits

Complex<double> ParseTerm(TokenStream &toks);

// Number -> (- | +) digits | digits
double ParseNumber(TokenStream &toks) {
  Token t;
  if (!(toks >> t)) throw std::runtime_error("Expected sign or number");

  switch (t.type) {
    case '+':
      if (!(toks >> t) || t.type != 'n')
        throw std::runtime_error("Expected number");
      return t.value;
    case '-':
      if (!(toks >> t) || t.type != 'n')
        throw std::runtime_error("Expected number");
      return t.value * -1;
    case 'n':
      return t.value;
    default:
      throw std::runtime_error("Expected number");
  }
}

// Complex -> number number i
Complex<double> ParseComplex(TokenStream &toks) {
  double real{ParseNumber(toks)};
  double imag{ParseNumber(toks)};

  Token t;
  if (!(toks >> t)) throw std::runtime_error("expected i for imaginary part");
  return {real, imag};
}

Complex<double> ParseExpr(TokenStream &toks) {
  Complex term{ParseTerm(toks)};
  Token t;
  if (toks >> t) {
    switch (t.type) {
      case '+':
        return term + ParseExpr(toks);
      case '-':
        return term - ParseExpr(toks);
      default:
        throw std::runtime_error(
          std::string{"expected sign in expr but got: "} + t.type +
          "; with val: " + std::to_string(t.value));
    }
  } else {
    return term;
  }
}

// Term    -> Complex * Term | Complex
Complex<double> ParseTerm(TokenStream &toks) {
  Complex complex{ParseComplex(toks)};
  Token t;
  if (toks >> t) {
    switch (t.type) {
      case '*':
        return complex * ParseTerm(toks);
      default:
        toks.putback(t);
        return complex;
    }
  } else {
    return complex;
  }
}

TEST_CASE ("Test mult") {
    CHECK_EQ(Complex{3.0, 4.0} * Complex{2.0, 5.0}, Complex{-14.0, 23.0});
}

TEST_CASE ("Test exps") {
  std::stringstream test_input{"           "};
    CHECK_NOTHROW(Lexer(test_input));
  std::stringstream test_input_2{"3 + 3"};
    CHECK_NOTHROW(Lexer(test_input_2));
  std::stringstream test_input_3{"3 -3i"};
    CHECK_NOTHROW(Lexer(test_input_3));
  std::stringstream test_input_4{"3 -3i;"};
    CHECK_THROWS(Lexer(test_input_4));
  std::stringstream test_input_5{"3i"};
  // Passes because it only tokenizes, the parser should fail for this
    CHECK_NOTHROW(Lexer(test_input_5));
}

TEST_CASE ("Test values") {
  std::stringstream test_input{"3 -3i"};
  auto ts{Lexer(test_input)};
    CHECK_EQ(ParseExpr(ts), Complex<double>{3, -3});
  std::stringstream test_input_2{"3 + 5i - 2 -0i"};
  ts = Lexer(test_input_2);
    CHECK_EQ(ParseExpr(ts), Complex<double>{1, 5});
  std::stringstream test_input_3{"- 2 -0i * 5 + 11i * -6+0i"};
  ts = Lexer(test_input_3);
    CHECK_EQ(ParseExpr(ts), Complex<double>{60, 132});

  std::stringstream test_input_4{"- 20 -1i * 95 + 11i + -0+8i"};
  ts = Lexer(test_input_4);
    CHECK_EQ(ParseExpr(ts), Complex<double>{-1889, -307});
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
  UserIo io;
  io << "Suma, resta y multiplica numeros imaginarios.\n"
     << "Introduce una expresion:\n> ";
  std::string user_input{};
  if (!(io.GetInputFromUser())) return res;
  io.GetLine(user_input);
  std::stringstream istream{user_input};
  TokenStream toks = Lexer(istream);
  auto result{ParseExpr(toks)};
  auto sign{result.imag >= 0 ? '+' : '-'};
  io << "= " << result.real << ' ' << sign << ' ' << result.imag << "i\n";
  return res;
}