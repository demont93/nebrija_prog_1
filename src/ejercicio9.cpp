//===-- ejercicio9.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio9
/// ----------
/// Crear un array de números enteros e indicar cuántas veces aparece el número
/// 7.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <array>
#include <algorithm>
#include "user_io.h"
#include "utilities.h"
#include "doctest.h"

template<size_t SIZE>
std::size_t Times7(const std::array<int, SIZE> &arr) {
  return std::count(arr.begin(), arr.end(), 7);
}

TEST_CASE ("test Times7") {
  std::array arr{1, 2, 3, 4, 5, 6, 7};
  CHECK(1 == Times7(arr));
  std::array arr_2{7, 0, 0, 0};
  CHECK(1 == Times7(arr_2));
  std::array arr_3{0, 0, 0, 0};
  CHECK(0 == Times7(arr_3));
  std::array arr_4{7, 7, 7, 7, 7, 7, 7, 7};
  CHECK(8 == Times7(arr_4));
  std::array<int, 0> arr_5{};
  CHECK(0 == Times7(arr_5));
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
  std::array arr{3, 7, 5, 7, 7, 7, 3};
  io << "Hay exactamente " << Times7(arr) << " '7's en el array "
     << CollectionString(arr.begin(), arr.end()) << '\n';
  return res;
}
