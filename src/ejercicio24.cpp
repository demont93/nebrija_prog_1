//===-- ejercicio24.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio24
/// -----------
/// Realizar un programa que pida al usuario un número y almacene en un
/// std::vector sus factores (todos aquellos números menores que él por los que
/// puede ser dividido).
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
#include "user_io.h"
#include "doctest.h"
#include "utilities.h"

struct UnzippedFactors {
  std::vector<int64_t> first_half;
  std::vector<int64_t> second_half;
};

[[nodiscard]] std::vector<int64_t> CatReverseVector(UnzippedFactors &&fs);

[[nodiscard]] UnzippedFactors UnzipFactorPairs(int64_t factors_of);

std::vector<std::int64_t> Factors(std::int64_t n) {
  assert(n > 0 && "Cant output infinite factors of 0");
  UnzippedFactors fs{UnzipFactorPairs(n)};
  // Si el ultimo factor se repite porque la raiz de n es un natural, debemos
  // eliminar el repetido.
  if (fs.first_half.back() == fs.second_half.back())
    fs.second_half.pop_back();
  std::vector<int64_t> result{CatReverseVector(std::move(fs))};
  // Le hacemos pop al ultimo ya que son los factores menores a n y los
  // naturales son divisibles entre 1 y ellos mismos.
  result.pop_back();
  return result;
}

/// Concatena vector 1 con vector 2 en reverso.
/// Ejemplo  UnzippedFactors{ v1: 1 2 3 4 5, v2: 10 9 8 7 6 }
/// Resultado v3 = 1 2 3 4 5 6 7 8 9 10
/// @param  fs Unzipped factors in struct
/// @return v1 ++ (rev v2)
std::vector<int64_t> CatReverseVector(UnzippedFactors &&fs) {
  std::copy(fs.second_half.rbegin(), fs.second_half.rend(),
            std::back_inserter(fs.first_half));
  return fs.first_half;
}

/// Obtiene el unzip de los pares de factores de _factors_of_ dentro de un
/// struct.
UnzippedFactors UnzipFactorPairs(int64_t factors_of) {
  int64_t check_up_to{static_cast<std::int64_t>(
                      std::sqrt(static_cast<long double>(factors_of)))};
  std::vector<int64_t> first_half_factors{};
  std::vector<int64_t> second_half_factors{};

  for (int64_t i{1}; i <= check_up_to; ++i) {
    if (factors_of % i == 0) {
      first_half_factors.push_back(i);
      second_half_factors.push_back(factors_of / i);
    }
  }
  return {first_half_factors, second_half_factors};
}

TEST_CASE("test factors") {
  using longvec = std::vector<int64_t>;
  CHECK(Factors(1).empty());
  CHECK(Factors(2) == longvec{1});
  CHECK(Factors(10) == (longvec{1, 2, 5}));
  CHECK(Factors(32) == (longvec{1, 2, 4, 8, 16}));
  CHECK(Factors(29) == longvec{1});
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
      io << "Introduce un entero n tal que 0 < n < 2^63:\n";
      if (!io.GetInputFromUser()) return 0;
      std::int64_t n;
      io.Token(n);
      if (n <= 0) {
        io << "Debes introducir un numero entre mayor a 0.\n";
        continue;
      } else {
        std::vector<std::int64_t> factors{Factors(n)};
        io << "Los factores de " << n << " son: "
           << CollectionString(factors.begin(), factors.end()) << '\n';
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
