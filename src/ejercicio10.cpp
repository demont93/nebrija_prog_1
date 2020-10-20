//===-- ejercicio10.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio10
/// -----------
/// Crear un programa que calcule la media de un array de números enteros.
/// Restricciones:  Suma del array < 2^31
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <array>
#include <numeric>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

template<std::size_t SIZE>
double MeanArr(const std::array<int, SIZE> &arr) {
  assert(SIZE != 0 && "Can't compute the mean of an empty array");
  int sum{std::accumulate(arr.begin(), arr.end(), 0)};
  return sum / static_cast<double>(SIZE);
}

TEST_CASE("test mean") {
  std::array arr{5, 5, 5, 5, 5, 5};
  CHECK(MeanArr(arr) == 5);
  std::array arr_2{5, 5, 5, 5, 5};
  CHECK(MeanArr(arr_2) == 5);
  std::array arr_3{5, 5};
  CHECK(MeanArr(arr_3) == 5);
  std::array arr_5{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  CHECK(MeanArr(arr_5) == 5.5);
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
  std::array arr{1, 2, 3, 4, 532, 6, 134};
  io << "La media aritmetica de " << CollectionString(arr.begin(), arr.end())
     << " es: " << MeanArr(arr) << '\n';
  return res;
}
