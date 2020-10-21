//===-- ejercicio2.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio2
/// ----------
/// Crear un programa que muestre por pantalla las tres posiciones en las que
/// aparece el texto "tri" en el siguiente texto: "Tres tristes tigres comen
/// trigo en un trigal"
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <ostream>
#include <cstring>
#include "user_io.h"
#include "doctest.h"

constexpr const char *const kPhrase{
  "Tres tristes tigres comen trigo en un trigal"};
constexpr const char *const kSubs{"tri"};

template<typename T>
void PositionOfTri(T& output) {
  const char* cursor{kPhrase};
  while ((cursor = strstr(cursor, kSubs)) != nullptr) {
    output << (cursor - kPhrase) << " ";
    ++cursor;
  }
  output << '\n';
}

TEST_CASE ("testing correct output of tri") {
  std::stringstream ss;
  PositionOfTri(ss);
  CHECK(ss.str() == "5 26 38 \n");
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
  io << kPhrase << " contiene " << kSubs << " en las posiciones:\n";
  PositionOfTri(io);
  return res;
}