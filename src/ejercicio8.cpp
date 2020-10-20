//===-- ejercicio8.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio8
/// ----------
/// Pedir al usuario que introduzca un texto por teclado y mostrar todas las
/// palabras que empiecen por "a".
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "doctest.h"
#include "user_io.h"
#include <cstring>

inline bool IsA(const char &c) {
  return c == 'a' || c == 'A';
}

int TimesBeginA(const std::string &line) {
  size_t counter{0};
  bool is_in_word{false};
  for (const char &c : line) {
    bool is_space{static_cast<bool>(isspace(c))};
    if (!is_space && !is_in_word) {
      is_in_word = true;
      if (IsA(c)) ++counter;
    } else if (is_space && is_in_word) {
      is_in_word = false;
    }
  }
  return counter;
}

TEST_CASE ("test TimesBeginA") {
  CHECK(TimesBeginA("None start 0 with letter-a") == 0);
  CHECK(TimesBeginA("All are A4 aaaaaaa") == 4);
  CHECK(TimesBeginA("Some start with a but just 1") == 1);
  CHECK(TimesBeginA("a a a a a A A A a a A a") == 12);
  CHECK(TimesBeginA("a a a a a a a a a a a a ") == 12);
  CHECK(TimesBeginA("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 1);
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;

  UserIO io;
  io << "Introduce una linea de texto: ";
  if (!io.GetInputFromUser()) return 0;
  std::string user_input{};
  io.GetLine(user_input);
  io << "Palabras que comienzan con 'a' o 'A': "
     << TimesBeginA(user_input) << '\n';
  return res;
}