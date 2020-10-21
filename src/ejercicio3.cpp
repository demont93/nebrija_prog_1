//===-- ejercicio3.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio3
/// ----------
/// A partir del texto "En un lugar de la Mancha, de cuyo nombre no quiero
/// acordarme" crear un programa que muestre por pantalla dos textos: lo que hay
/// antes de Mancha (En un lugar de la ) y lo que hay después (, de cuyo nombre
/// no quiero acordarme).
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "user_io.h"
#include "doctest.h"

constexpr const char *const kPhrase{
  "En un lugar de la Mancha, de cuyo nombre no quiero acordarme"};

template<typename T>
constexpr void BeforeAfterMancha(T &output) {
  const char *cursor{kPhrase};
  while (*cursor != 'M') {
    output << *cursor;
    ++cursor;
  }
  while (*cursor != ',') ++cursor;
  output << cursor << '\n';
}

TEST_CASE ("should ") {
  std::stringstream ss;
  BeforeAfterMancha(ss);
    CHECK(
    ss.str() == "En un lugar de la , de cuyo nombre no quiero acordarme\n");
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;
  UserIo io;
  io << "Si quitamos la palabra Mancha de: " << kPhrase << '\n'
     << "queda: ";
  BeforeAfterMancha(io);
  return res;
}
