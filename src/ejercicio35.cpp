//===-- ejercicio35.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio35
/// ===========
/// Introducir nota numérica por consola y devolver calificación (sobresaliente,
/// Notable, Aprobado, Suspenso)
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"

// FIXME Dont know about grades in spain.
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