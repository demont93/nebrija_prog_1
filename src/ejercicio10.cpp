//===-- ejercicio10.cpp -----------------------------------------*- C++ -*-===//
//
// Ejercicio10
// Crear un programa que calcule la media de un array de números enteros.
// Restricciones:  Suma del array < 2^31
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <array>
#include "utilities.h"
#include "user_io.h"

template<std::size_t SIZE>
double MeanArr(const std::array<int, SIZE> &arr) {
  // Cual es el promedio de un array vacio? tambien podriamos retornar option
  if (SIZE <= 0) return 0;
  int sum{0};
  for (const int &elem : arr)
    sum += elem;
  // Static cast a double para recibir double
  // Es bueno usar static_cast para poder ver explicitamente donde se hacen las
  // conversiones. Los bugs de producidos por casteos implicitos son muy
  // dificiles de encontrar y entender.
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
  // Test();
  UserIO io;
  std::array arr{1, 2, 3, 4, 532, 6, 134};
  io << "La media aritmetica de " << CollectionString(arr.begin(), arr.end())
     << " es: " << MeanArr(arr) << '\n';
}

