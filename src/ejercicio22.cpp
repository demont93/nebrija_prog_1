//===-- ejercicio22.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio22
/// -----------
/// Crear un programa que calcule los n primeros números de la Serie de
/// Fibonacci. El programa debe pedir al usuarios cuántos números desea calcular,
/// y continuación estos se deben calcular y almacenar en el tipo de datos
/// oportuno.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <vector>
#include <iostream>
#include "user_io.h"
#include "utilities.h"
#include "doctest.h"

std::vector<int64_t> NFib(int n) {
  assert(n >= 0 && "Can't compute NFib with negative number.");
  assert(n <= 93 && "Calling NFib with  > 93 produces overflow.");
  if (n == 0) return {};
  if (n == 1) return {0};
  if (n == 2) return {0, 1};

  std::vector<std::int64_t> fibos{0, 1};
  fibos.reserve(static_cast<size_t>(n));
  int operations{n - 2};
  for (int i{0}; i < operations; ++i) {
    auto last_it = fibos.rbegin();
    fibos.push_back(*last_it + *(++last_it));
  }
  return fibos;
}

TEST_CASE("test NFib") {
  using fibvec = std::vector<int64_t>;
  CHECK(NFib(10) == (fibvec{0, 1, 1, 2, 3, 5, 8, 13, 21, 34}));
  CHECK(NFib(0).empty());
  CHECK(NFib(1) == fibvec{0});
  CHECK(NFib(2) == (fibvec{0, 1}));
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
      io << "Introduce un entero n tal que 0 <= n <= 93:\n";
      if (!io.GetInputFromUser()) return 0;
      int n;
      io.Token(n);
      if (n < 0 || n > 93) {
        io << "Debes introducir un numero entre [0, 93].\n";
        continue;
      } else {
        auto lista{NFib(n)};
        io << "Lista de Fibonacci hasta " << n << '\n'
           << CollectionString(lista.begin(), lista.end()) << '\n';
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