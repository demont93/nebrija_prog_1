//===-- ejercicio36.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio36
/// Mostrar el abecedario por pantalla con un unico bucle.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "user_io.h"

template<typename T>
constexpr void Abc(T &output) noexcept {
  for (char c{'a'}; c <= 'z'; ++c)
    output << c << ' ';
  output << '\n';
}

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

  UserIo io;
  Abc(io);

  return res;
}