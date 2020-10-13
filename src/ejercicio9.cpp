//
// Created by demont93 on 10/10/20.
//

#include <iostream>
#include <cassert>
#include <array>

// Ejercicio9
// Crear un array de números enteros e indicar cuántas veces aparece el número 7.
template<std::size_t SIZE>
std::size_t Times7(const std::array<int, SIZE> &arr) {
  std::size_t counter{0};
  for (std::size_t i{0}; i < arr.size(); ++i) {
    if (arr[i] == 7) {
      ++counter;
    }
  }
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
  std::array arr{3, 7, 5, 7, 7, 7, 3};
  std::cout << "Hay exactamente " << Times7(arr)
            << " '7's en el array ";
  for (int i{0}; i < 7; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}