#include <iostream>
#include <algorithm>
#include <cassert>
#include <array>
#include "utilities.h"

// Ejercicio11
// Crear un array de números enteros (entre el 1 y el 10) e indicar cuál es el
// número que más veces aparece (y cuántas veces aparece).
template<std::size_t SIZE>
std::pair<int, int> ElemFreq(const std::array<int, SIZE> &arr) {
  assert(std::none_of(arr.begin(), arr.end(), [](const int& n) {return n < 1 || n > 10;}));
  assert(SIZE > 0); // No podemos calcular el elem mas frecuente si esta vacio

  // Este array representa:
  //    Indices: Representa cada uno de los 10 numeros del 0 - 9
  //             Para obtener el numero, le sumamos 1 al indice, con lo cual
  //             el 0 se convierte en 1, el 1 en 2, el 2 en 3...
  //    Valores: Representa la frecuencia con la cual aparece cada numero.
  //
  // Ejemplo: El array [1,5,4,5,6] estaria representado de la siguiente forma.
  //
  // Indices    0     1     2     3     4     5     6     7     8     9
  // Valores: [ 1 ] [ 0 ] [ 0 ] [ 1 ] [ 2 ] [ 1 ] [ 0 ] [ 0 ] [ 0 ] [ 0 ]
  //
  std::array<int, 10> freqs{}; // inicializa un arr de 10 elementos con 0

  // leemos el los numeros y los sumamos en el indice del array
  for (std::size_t i{0}; i < SIZE; ++i) {
    ++freqs[arr[i] - 1];
  }
  // Buscamos el mayor numero mayor en el array.
  std::array<int,10>::iterator max_element{std::max_element(freqs.begin(), freqs.end())};
  // El numero de mayor frecuencia esta representado por su posicion + 1
  int most_frequent_number = static_cast<int>(max_element - freqs.begin()) + 1;
  // Retorna el primer elemento con mas frecuencia y cuantas veces
  return std::pair{most_frequent_number, *max_element};
}

void Test() {
  std::array arr{1, 1, 1, 1, 1, 1};
  assert(ElemFreq(arr) == std::pair(1, 6));
  std::array arr_2{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  assert(ElemFreq(arr_2) == std::pair(4, 4));
  std::array arr_3{1, 2, 3};
  assert(ElemFreq(arr_3) == std::pair(1, 1));
}

int main() {
  // Test();
  std::array arr{1, 2, 2, 3, 1, 4, 4, 2, 2, 10};
  std::cout << "Elemento que aparece con mas frecuencia en ";
  PrintCollection(arr.begin(), arr.end());
  std::pair<int, int> res{ElemFreq(arr)};
  std::cout << " es el " << res.first << ", " << res.second
            << " veces" << std::endl;
}