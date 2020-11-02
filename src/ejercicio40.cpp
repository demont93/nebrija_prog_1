//===-- ejercicio40.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio40
/// ===========
/// Pedir al usuario día, mes y año de nacimiento. Devolver signo de zodiaco y
/// edad actual.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"

TEST_CASE ("") {
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