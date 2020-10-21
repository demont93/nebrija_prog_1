//===-- ejercicio5.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio5
/// ----------
/// Realizar un programa que recorra un array de valores enteros y busque si
/// contiene el número 7. En caso de que lo contenga imprimir por pantalla la
/// primera posición en la que aparezca.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <array>
#include <optional>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

template<std::size_t SIZE>
std::optional<size_t> PositionOfFirst7(const std::array<int, SIZE> arr) {
  for (size_t i{0}; i < SIZE; ++i)
    if (arr[i] == 7) return i;
  return {};
}

TEST_CASE ("test position of 7") {
  SUBCASE("test 0") {
    const std::array<int, 0> arr_1{};
    CHECK_EQ(PositionOfFirst7(arr_1), std::nullopt);
    const std::array arr_2{0, 0, 0, 0};
    CHECK_EQ(PositionOfFirst7(arr_2), std::nullopt);
  }
  SUBCASE("test 1") {
    const std::array arr_1{7, 0, 0, 0};
    CHECK_EQ(PositionOfFirst7(arr_1), std::optional{0});
    const std::array arr_2{1, 2, 7};
    CHECK_EQ(PositionOfFirst7(arr_2), std::optional{2});
    const std::array arr_3{1, 2, 3, 4, 5, 6, 7};
    CHECK_EQ(PositionOfFirst7(arr_3), std::optional{6});
  }
  SUBCASE("test many") {
    const std::array arr_1{7,7,7,7,7,7,7,7,7,7,7,7};
    CHECK_EQ(PositionOfFirst7(arr_1), std::optional{0});
    const std::array arr_2{2,7,0,2,3,93,7};
    CHECK_EQ(PositionOfFirst7(arr_2), std::optional{1});
  }
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
  const std::array arr{3, 34, 34, 2, 5, 252834, 6, 7, 5484, 0, 0, 1};
  const std::optional<size_t> index = PositionOfFirst7(arr);
  if (index) {
    io << "First '7' found in: " << CollectionString(arr.begin(), arr.end())
       << " at index: " << *index << '\n';
  } else {
    io << "Elem '7' not found in: "
       << CollectionString(arr.begin(), arr.end()) << '\n';
  }
  return res;
}