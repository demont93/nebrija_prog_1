//
// Created by demont93 on 10/10/20.
//

#include <iostream>
#include <cassert>
#include <utilities.h>
#include <array>

// Ejercicio10
// Crear un programa que calcule la media de un array de números enteros.
// Constraints sum of arr < 2^31
template<std::size_t SIZE>
double MeanArr(const std::array<int, SIZE> &arr) {
  // cual es el promedio de un array vacio? tambien podriamos retornar nullopt
  if (SIZE <= 0) return 0;
  int sum{0};
  for (const int &elem : arr)
    sum += elem;
  // static cast a double para recibir double
  return sum / static_cast<double>(SIZE);
}

void Test() {
  std::array arr{5, 5, 5, 5, 5, 5};
  assert(MeanArr(arr) == 5);
  assert(MeanArr(arr) == 5);
  assert(MeanArr(arr) == 5);
  assert(MeanArr(arr) == 0);
  std::array arr_2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  assert(MeanArr(arr_2) == 5.5);
}

int main() {
  Test();
  std::array arr{1, 2, 3, 4, 532, 6, 134};
  std::cout << "La media aritmetica de ";
  PrintCollection(arr.begin(), arr.end());
  std::cout << " es: " << MeanArr(arr) << std::endl;
}

