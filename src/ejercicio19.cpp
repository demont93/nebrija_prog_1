//===-- ejercicio19.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio19
/// -----------
/// Pedir al usuario un número y mostrar por pantalla si dicho número es primo o
/// no (usando el bucle while).
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cmath>
#include <array>
#include <vector>
#include <cassert>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"


/// Calcula el "Sieve of Erathosthenes" hasta n.
/// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// Using vector because it packs bools
std::vector<bool> Sieve(int for_n) {
  assert(for_n >= 0 && "Cant compute a sieve for a number less than 0");
  // Special cases
  if (for_n == 0) return {false};
  if (for_n == 1) return {false, false};

  // To get all sieve primes, only need to loop until sqrt of n
  auto up_to{static_cast<size_t>(ceil(sqrt(static_cast<double>(for_n)))) + 1};

  std::vector<bool> sieve(for_n + 1, true);
  sieve[0] = false;
  sieve[1] = false;

  for (size_t i{0}; i <= up_to; ++i) {
    if (sieve[i]) {
      for (size_t k{i*2}; k <= for_n; k += i)
        sieve[k] = false;
    }
  }

  return sieve;
}

bool IsPrime(int n) {
  assert(n >= 0 && "IsPrime should not have a negative parameter.");
  return Sieve(n)[n];
}

TEST_CASE("test IsPrime") {
  CHECK(!IsPrime(0));
  CHECK(!IsPrime(1));
  CHECK(IsPrime(2));
  CHECK(!IsPrime(171));
  CHECK(IsPrime(197));
  CHECK(IsPrime(5387));
  CHECK(!IsPrime(4927));
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;

  UserIO io{};
  while (true) {
    try {
      int n;
      io << "Introduce un numero natural para saber si es primo: ";
      if (!io.GetInputFromUser())
        return 0;
      io.Token(n);
      if (n < 0) {
        io << n << " no es natural.\nIntentalo de nuevo.";
        continue;
      }
      if (IsPrime(n))
        io << n << " es primo.\n";
      else
        io << n << " no es primo.\n";
      return res;
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}