//===-- ejercicio11.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio11
/// Crear un array de números enteros (entre el 1 y el 10) e indicar cuál es el
/// número que más veces aparece (y cuántas veces aparece).
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <algorithm>
#include <cassert>
#include <array>
#include "utilities.h"
#include "user_io.h"
#include "doctest.h"

// 1. Create an array [0,9] to represent [1,10].
// 2. Store frequency by scanning.
// 3. Take greatest first frequency.
// 4. Calculate number from index.
template<std::size_t SIZE>
std::pair<int, int> ElemFreq(const std::array<int, SIZE> &arr) {
  assert(std::none_of(arr.begin(), arr.end(),
                      [](const int &n) { return n < 1 || n > 10; }));
  assert(SIZE > 0); // can't calculate freq of empty collection

  std::array<int, 10> freqs{};          // value init all to 0
  // Scan
  for (size_t i{0}; i < SIZE; ++i)
    ++freqs[arr[i] - 1];

  // Get max frequency
  auto max_frequency_pointer{std::max_element(freqs.begin(), freqs.end())};
  // Calculate number from index
  int frequent_number{
  static_cast<int>(max_frequency_pointer - freqs.begin()) + 1};

  return std::pair{frequent_number, *max_frequency_pointer};
}

TEST_CASE ("test ElemFreq") {
  std::array arr{1, 1, 1, 1, 1, 1};
  CHECK(ElemFreq(arr) == std::pair(1, 6));
  std::array arr_2{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  CHECK(ElemFreq(arr_2) == std::pair(4, 4));
  std::array arr_3{1, 2, 3};
  CHECK(ElemFreq(arr_3) == std::pair(1, 1));
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
  std::array arr{1, 2, 2, 3, 1, 4, 4, 2, 2, 10};
  io << "Elemento que aparece con mas frecuencia en "
     << CollectionString(arr.begin(), arr.end());
  std::pair<int, int> result{ElemFreq(arr)};
  io << " es el " << result.first << ", " << result.second
     << " veces" << '\n';
  return res;
}