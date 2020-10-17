//===-- ejercicio5.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio5
// Realizar un programa que recorra un array de valores enteros y busque si
// contiene el número 7. En caso de que lo contenga imprimir por pantalla la
// primera posición en la que aparezca.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <array>
#include <optional>
#include <cassert>
#include "utilities.h"
#include "user_io.h"

// Podemos usar parametros literales en el template. Aqui SIZE representa un num
// de tipo std::size_t, lo cual es un numero que puede representar la maxima
// cantidad de elementos dentro de un array.
// De la misma forma podriamos poner
// template<int N> haciendo que el compilador genere una funcion nueva para cada
// _n_ diferente con la que invoques la funcion.
// Esto es necesario para un array ya que su tamano forma parte de su tipo, es
// decir, array<int, 5> es un TIPO DIFERENTE  de array<int, 7>. Por lo tanto
// una funcion que acepta como parametro un array<int, 7> tiene un signature
// diferente a una que acepta un array<int,5>.
template<std::size_t SIZE>
std::optional<int> PositionOfFirst7(const std::array<int, SIZE> arr) {
  // Un tipo optional forma parte del stdlib desde C++17 y representa un tipo
  // que puede o no tener un valor adentro. Viene de la monada maybe en Haskell,
  // o del tipo <option> en Rust.
  for (size_t i{0}; i < SIZE; ++i)   // Usamos SIZE por su valor
    if (arr[i] == 7) return i;
  return {}; // devuelve nada
}

void Test() {
  const std::array arr{1, 2, 3, 4, 5, 6, 7};
  assert(PositionOfFirst7(arr) == std::optional{6});
  const std::array arr_2{7, 0, 0, 0};
  assert(PositionOfFirst7(arr_2) == std::optional{0});
  const std::array arr_3{0, 0, 0, 0};
  assert(PositionOfFirst7(arr_3) == std::nullopt); // nullopt representa nada
  const std::array<int, 0> arr_4{};
  assert(PositionOfFirst7(arr_4) == std::nullopt);
}

int main() {
  // Test();
  UserIO io;
  const std::array arr{3, 34, 34, 2, 5, 252834, 6, 7, 5484, 0, 0, 1};
  const std::optional<int> index = PositionOfFirst7(arr);
  if (index) {
    io << "First '7' found in: " << CollectionString(arr.begin(), arr.end())
       << " at index: " << *index << '\n';
  } else {
    io << "Elem '7' not found in: "
       << CollectionString(arr.begin(), arr.end()) << '\n';
  }
}
