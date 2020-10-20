//===-- ejercicio30.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio30
/// -----------
/// Crear una función que recorra un vector de números enteros positivos y
/// devuelva un vector con aquellos números que sean primos. Para ello se creará
/// previamente una función que diga si un número es primo o no.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <vector>
#include <any>
#include <cmath>
#include "doctest.h"
#include "user_io.h"
#include "utilities.h"

/// Sieve de Eratosthenes, permite encontrar numero primos hasta cierto numero
/// especificado durante la construccion. Es un objeto inmutable.
class Sieve {
 public:
  Sieve() = delete;

  /// Crea un Sieve a partir de un vector de bools. El vector representa cuales
  /// numero son primos por sus indices.
  explicit Sieve(std::vector<bool> &&table) : table{table} {
    if (table.empty())
      throw std::runtime_error(
        "No se puede construir un sieve de una tabla vacia");
  };

  /// Named constructor: Permite crear un sieve de tamano n + 1.
  static Sieve WithSize(const size_t size) {
    return Sieve{MakeSieve(size)};
  }

  /// Revisa si un numero es primo en la tabla con chequeo de indices. Si
  /// necesitas mas velocidad puedes evitar el check con IsPrimeUnchecked.
  [[nodiscard]] bool IsPrime(const size_t n) const {
    return table.at(n);
  }

  /// Revisa si un numero es primo en la tabla sin chequear los indices. Para
  /// una alternativa segura mira IsPrime.
  [[nodiscard]] bool IsPrimeUnchecked(const size_t n) const noexcept {
    return table[n];
  }

  /// Retorna el maximo numero que puedes preguntar si es primo.
  [[nodiscard]] size_t MaxPossiblePrime() const noexcept {
    return table.size() - 1;
  }

 private:
  const std::vector<bool> table;

  /// Contiene toda la logica para crear la tabla inicial a partir de n.
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

std::vector<size_t> TakePrimes(const std::vector<size_t> &numbers) {
  size_t max{
    static_cast<size_t>(*std::max_element(numbers.begin(), numbers.end()))};
  Sieve s{Sieve::WithSize(max)};
  std::vector<size_t> result;
  for (const size_t &n : numbers)
    if (s.IsPrimeUnchecked(n)) result.push_back(n);
  return result;
}

TEST_CASE ("test WithSize") {
    CHECK_NOTHROW(Sieve::WithSize(100));
    CHECK_NOTHROW(Sieve::WithSize(1));
    CHECK_NOTHROW(Sieve::WithSize(0));
}

TEST_CASE ("test constructor") {
    CHECK_NOTHROW(Sieve{std::vector{false, true}});
    CHECK_THROWS(Sieve{std::vector<bool>{}});
}

TEST_CASE ("test IsPrime") {
  Sieve s{Sieve::WithSize(20000000)};
    CHECK(s.IsPrimeUnchecked(3));
    CHECK(s.IsPrimeUnchecked(5));
    CHECK(s.IsPrimeUnchecked(7));
    CHECK(s.IsPrimeUnchecked(19));
    CHECK(s.IsPrimeUnchecked(23));
    CHECK(s.IsPrimeUnchecked(15485867));

    CHECK(!s.IsPrimeUnchecked(4));
    CHECK(!s.IsPrimeUnchecked(9));
    CHECK(!s.IsPrimeUnchecked(21));
    CHECK(!s.IsPrimeUnchecked(15485866));
}

TEST_CASE ("test take primes") {
  std::vector<size_t> given{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                            15, 16};
    CHECK_EQ(TakePrimes(given), std::vector<size_t>{2, 3, 5, 7, 11, 13});
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
  std::vector<size_t> numbers{1, 2, 4, 5, 20, 39, 3498734, 98734, 5485863};
  io << "A partir de la coleccion "
     << CollectionString(numbers.begin(), numbers.end()) << '\n';
  std::vector primes{TakePrimes(numbers)};
  io << "Obtenemos los primos "
     << CollectionString(primes.begin(), primes.end()) << '\n';
  return res;
}

