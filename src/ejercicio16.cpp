//===-- ejercicio16.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio16
/// Pedir un número al usuario y calcular el sumatorio desde 1 hasta dicho
/// número.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <stdexcept>
#include "user_io.h"
#include "doctest.h"

constexpr int kMax{65535};

int Series(const int n) {
  assert(n >= 0 && n <= kMax);
  auto big_n = static_cast<std::int64_t>(n);
  return big_n * (big_n + 1) / 2.0;
}

TEST_CASE("test Series") {
  CHECK_EQ(Series(10), 55);
  CHECK_EQ(Series(0), 0);
  CHECK_EQ(Series(100), 5050);
  CHECK_EQ(Series(65535), 2147450880);
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
  int n;
  while (true) {
    try {
      io << "Introduce un numero n: ";
      if (!io.GetInputFromUser()) return 0;
      io.Token(n);
      if (n > kMax || n < 0) {
        io << "El numero debe cumplir 0 >= n >= " << kMax << '\n';
      } else {
        io << "Sumatorio de 1 hasta " << n << ": " << Series(n) << '\n';
        return res;
      }
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err("\n");
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err("\n");
    }
  }
}