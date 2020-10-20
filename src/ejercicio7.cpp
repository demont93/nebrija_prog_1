//===-- ejercicio7.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio7
/// ----------
/// Pedir al usuario que introduzca un texto por teclado y mostrar por pantalla
/// el número de veces que aparece la vocal "a".
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include <algorithm>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

int TimesA(const std::string &s) {
  return std::count_if(s.begin(), s.end(), [](const char &c) {
    return c == 'a' || c == 'A';
  });
}

TEST_CASE ("test times 'a' in string") {
  CHECK_EQ(TimesA(""), 0);
  CHECK_EQ(TimesA(""), 0);
  CHECK_EQ(TimesA("10aaaaaaAaaa"), 10);
  CHECK_EQ(TimesA("0"), 0);
  CHECK_EQ(TimesA("Es la unica culpikeubo, la unica culpa que tengo."), 5);
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
  io << "Introduce una oracion preferiblemente con 'a' o 'A': ";
  std::string user_input{};
  if (!io.GetInputFromUser()) return 0;
  io.GetLine(user_input);
  io << "'A' or 'a' in text: " << TimesA(user_input) << '\n';
  return res;
}