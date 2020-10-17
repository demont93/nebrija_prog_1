//===-- ejercicio11.cpp -----------------------------------------*- C++ -*-===//
//
// Ejercicio11
// Crear un array de números enteros (entre el 1 y el 10) e indicar cuál es el
// número que más veces aparece (y cuántas veces aparece).
//
//===----------------------------------------------------------------------===//

#include <algorithm>
#include <cassert>
#include <array>
#include "utilities.h"
#include "user_io.h"

// Buscamos el numero entre [1,10] con mayor frecuencia (que mas aparece)
// Esta es la idea general de como funciona el algoritmo.
//
// Creamos un array en el cual:
//    Indices: Representan cada uno de los 10 numeros del [0, 9]
//             Para obtener el numero, le sumamos 1 al indice, con lo cual
//             el 0 se convierte en 1, el 1 en 2, el 2 en 3...
//    Valores: Representan la frecuencia con la cual aparece cada numero.
//
// Luego scaneamos los valores y los sumamos en nuestro array de frecuencias.
// Al terminar nos quedan todas las  frecuencias almacenadas de la siguiente
// forma:
// Ejemplo: El array [1,5,4,5,6] estaria representado de la siguiente forma.
//
// Indices    0     1     2     3     4     5     6     7     8     9
// Valores: [ 1 ] [ 0 ] [ 0 ] [ 1 ] [ 2 ] [ 1 ] [ 0 ] [ 0 ] [ 0 ] [ 0 ]
//                                    ^
//                                    |
// Para terminar buscamos la frecuencia mayor. En el ejemplo era el indice 4, si
// le sumamos 1 nos da el numero 5, con lo cual retornamos el numero 5 y la freq
// 2.
template<std::size_t SIZE>
std::pair<int, int> ElemFreq(const std::array<int, SIZE> &arr) {
  assert(std::none_of(arr.begin(), arr.end(),
                      [](const int &n) { return n < 1 || n > 10; }));
  assert(SIZE > 0); // No podemos calcular el elem mas frecuente si esta vacio

  std::array<int, 10> freqs{};          // el array, {} inicializa a 0 completo
  for (size_t i{0}; i < SIZE; ++i)      // el scan
    ++freqs[arr[i] - 1];

  auto max_frequency_pointer{std::max_element(freqs.begin(), freqs.end())};
  int frequent_number{
    // Si restamos el puntero con el inicio, nos da el indice
    static_cast<int>(max_frequency_pointer - freqs.begin()) + 1};

  return std::pair{frequent_number, *max_frequency_pointer};
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
  UserIO io;
  std::array arr{1, 2, 2, 3, 1, 4, 4, 2, 2, 10};
  io << "Elemento que aparece con mas frecuencia en "
     << CollectionString(arr.begin(), arr.end());
  std::pair<int, int> res{ElemFreq(arr)};
  io << " es el " << res.first << ", " << res.second
     << " veces" << '\n';
}