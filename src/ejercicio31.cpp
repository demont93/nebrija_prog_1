//===-- ejercicio31.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio31
/// -----------
/// Crear una función que devuelva un vector con los n primeros números primos.
/// El número n se le debe pasar a la función como parámetro.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <vector>
#include <cmath>
#include "utilities.h"
#include "doctest.h"
#include "user_io.h"

class Sieve {
 public:
  Sieve() = delete;

  explicit Sieve(std::vector<bool> &&table) : table{table} {
    if (table.empty())
      throw std::runtime_error(
        "No se puede construir un sieve de una tabla vacia");
  };

  static Sieve WithSize(const size_t size) {
    return Sieve{MakeSieve(size)};
  }

  [[nodiscard]] bool IsPrimeUnchecked(const size_t n) const noexcept {
    return table[n];
  }

 private:
  const std::vector<bool> table;

  static std::vector<bool> MakeSieve(size_t for_n) {
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
        for (size_t k{i * 2}; k <= for_n; k += i)
          sieve[k] = false;
      }
    }

    return sieve;
  }
};

template<typename T>
void PrimesUpTo(size_t up_to, T &output) {
  Sieve s{Sieve::WithSize(up_to)};
  std::vector<size_t> result;
  for (size_t n{0}; n <= up_to; ++n)
    if (s.IsPrimeUnchecked(n)) output << n << '\n';
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
  io << "Enter a number:\n";
  if (!io.GetInputFromUser()) return res;
  size_t n;
  io.Token(n);
  io << "Primes up to " << n << ":\n";
  PrimesUpTo(n, io);
  return res;
}