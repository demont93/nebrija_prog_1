//===-- ejercicio17.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio17
/// Pedir tres números al usario: _a_, _b_ y _c_. Crear un vector que contenga
/// todos los números múltiplos de _c_ que hay entre [_a_, _b_].
/// Restricciones : a <= b
///                 0 < a, b, c <= 2^31
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <vector>
#include <cmath>
#include "utilities.h"
#include "doctest.h"
#include "user_io.h"

std::vector<int> MultiplesOfBetween(int multiples_of, int from, int to) {
  assert(multiples_of > 0 && from > 0 && to > 0);
  assert(from <= to);
  std::vector<int> new_v{};
  // Empezamos por el primer multiplo >= _to_
  int multiple =
  int(std::ceil(from / static_cast<double>(multiples_of)) * multiples_of);
  for (; multiple <= to; multiple += multiples_of)
    new_v.push_back(multiple);
  return new_v;
}

TEST_CASE("test MultipleOfBetween") {
  CHECK_EQ(MultiplesOfBetween(5, 10, 20), (std::vector{10, 15, 20}));
  CHECK(MultiplesOfBetween(100, 50, 60).empty());
  CHECK_EQ(MultiplesOfBetween(1, 1000, 1002), (std::vector{1000, 1001, 1002}));
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

  while (true) {
    try {
      int a, b, c;
      io << "Introduce 3 \"a,b,c\" separados por espacios para recibir todos "
         << "los multiplos de \"c\" entre \"a\" y \"b\":\n";
      if (!io.GetInputFromUser()) return 0;
      io.Token(a);
      io.Token(b);
      io.Token(c);
      if (a > b) {
        io << "'a' no puede ser mayor a 'b'\n"
           << "Intenta de nuevo\n";
      } else if (a < 1 || b < 1 || c < 1) {
        io << "Ningun numero puede ser menor a 1\n"
           << "Intenta de nuevo\n";
      } else {
        std::vector result{MultiplesOfBetween(c, a, b)};
        io << CollectionString(result.begin(), result.end()) << '\n';
        return res;
      }
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err('\n');
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}