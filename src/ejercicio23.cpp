//===-- ejercicio23.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Realizar un programa que pida al usuario un número y muestre por pantalla su
/// factorial.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <iostream>
#include "user_io.h"
#include "doctest.h"

int64_t Factorial(int n) {
  assert(n <= 20 && n >= 0);
  if (n == 0) return 1;

  int64_t accumulator{n};
  while (--n) accumulator *= n;

  return accumulator;
};

TEST_CASE ("test Factorial") {
  CHECK_EQ(Factorial(0), 1);
  CHECK_EQ(Factorial(1), 1);
  CHECK_EQ(Factorial(20), 2432902008176640000);
  CHECK_EQ(Factorial(10), 3628800);
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;

  UserIo io{};
  while (true) {
    try {
      io << "Introduce un entero n tal que 0 <= n <= 20:\n";
      if (!io.GetInputFromUser()) return 0;
      int n;
      io.Token(n);
      if (n < 0 || n > 20) {
        io << "Debes introducir un numero entre [0, 20].\n";
        continue;
      } else {
        io << "Factorial de " << n << ": "
           << Factorial(n) << '\n';
        return res;
      }
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}