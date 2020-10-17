//===-- ejercicio6.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio6
// Realizar un programa que recorra un array de valores enteros y busque si
// contiene el número 7. En caso de que lo contenga imprimir por pantalla todas
// las posiciones en las que lo contiene.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <array>
#include <sstream>
#include <cassert>
#include "user_io.h"

template<std::size_t SIZE, typename T>
void PrintAllPositionsOf7(const std::array<int, SIZE> &arr, T &output) {
  // Busqueda lineal, si lo encontramos imprimimos el indice
  for (int i{0}; i < SIZE; ++i)
    if (arr[i] == 7) output << i << " ";
  output << '\n';
}

void Test() {
  std::stringstream ss;

  std::array arr{1, 2, 3, 4, 5, 6, 7};
  PrintAllPositionsOf7(arr, ss);
  assert(ss.str() == "6 \n");
  ss.str(""); // reset

  std::array arr_2{7, 0, 0, 0};
  PrintAllPositionsOf7(arr_2, ss);
  assert(ss.str() == "0 \n");
  ss.str(""); // reset

  std::array arr_3{0, 0, 0, 0};
  PrintAllPositionsOf7(arr_3, ss);
  assert(ss.str() == "\n");
  ss.str(""); // reset

  std::array arr_4{7, 7, 7, 7, 7, 7, 7, 7};
  PrintAllPositionsOf7(arr_4, ss);
  assert(ss.str() == "0 1 2 3 4 5 6 7 \n");
  ss.str(""); // reset
}

int main() {
  // Test();
  UserIO io;
  std::array arr_4{7, 7, 7, 7, 7, 7, 7, 7};
  io << "En el siguiente array, hemos encontrado el 7 en las posiciones: \n";
  PrintAllPositionsOf7(arr_4, io);
  io << '\n';
}