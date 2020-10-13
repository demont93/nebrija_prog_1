//
// Created by demont93 on 10/9/20.
//

#include <iostream>
#include <array>
#include <optional>
#include <cassert>
#include "utilities.h"

// Ejercicio5
// Realizar un programa que recorra un array de valores enteros y busque si
// contiene el número 7. En caso de que lo contenga imprimir por pantalla la
// primera posición en la que aparezca.
template<std::size_t SIZE>
std::optional<int> PrintElemArray(const std::array<int, SIZE> arr) {
  for (size_t i{0}; i < arr.size(); ++i) {
    if (arr[i] == 7) return i;
  }
  return {};
}

void Test() {
  const std::array arr{1, 2, 3, 4, 5, 6, 7};
  assert(PrintElemArray(arr) == std::optional{6});
  const std::array arr_2{7, 0, 0, 0};
  assert(PrintElemArray(arr_2) == std::optional{0});
  const std::array arr_3{0, 0, 0, 0};
  assert(PrintElemArray(arr_3) == std::nullopt);
  const std::array<int, 0> arr_4{};
  assert(PrintElemArray(arr_4) == std::nullopt);
}

int main() {
  // Test();
  const std::array arr{3, 34, 34, 2, 5, 252834, 6, 7, 5484, 0, 0, 1};
  const std::optional<int> index = PrintElemArray(arr);
  if (index) {
    std::cout << "First '7' found in: ";
    PrintCollection(arr.begin(), arr.end());
    std::cout << " at index: " << *index << std::endl;
  } else {
    std::cout << "Elem '7' not found in: ";
    PrintCollection(arr.begin(), arr.end());
    std::cout << std::endl;
  }
}
