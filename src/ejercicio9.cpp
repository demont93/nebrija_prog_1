//===-- ejercicio9.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio9
// Crear un array de números enteros e indicar cuántas veces aparece el número
// 7.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cassert>
#include <array>
#include "user_io.h"
#include "utilities.h"

template<std::size_t SIZE>
std::size_t Times7(const std::array<int, SIZE> &arr) {
  std::size_t counter{0};
  for (const int &n : arr)
    if (n == 7) ++counter;
  return counter;
}

void Test() {
  std::array arr{1, 2, 3, 4, 5, 6, 7};
  assert(1 == Times7(arr));
  std::array arr_2{7, 0, 0, 0};
  assert(1 == Times7(arr_2));
  std::array arr_3{0, 0, 0, 0};
  assert(0 == Times7(arr_3));
  std::array arr_4{7, 7, 7, 7, 7, 7, 7, 7};
  assert(8 == Times7(arr_4));
  std::array<int, 0> arr_5{};
  assert(0 == Times7(arr_5));
}

int main() {
  // Test();
  UserIO io;
  std::array arr{3, 7, 5, 7, 7, 7, 3};
  io << "Hay exactamente " << Times7(arr) << " '7's en el array "
     << CollectionString(arr.begin(), arr.end()) << '\n';
}