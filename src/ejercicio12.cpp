#include <cassert>
#include <array>
#include <iostream>

// Ejercicio12
// Crear un array de números enteros e indicar cuántas veces seguidas aparece
// como máximo el número 7. Es decir, para el array {1,2,7,7,4,3,3,7,7,7,2} el
// número máximo de veces seguidas que aparece el 7 es 3. Aparece 2 veces
// seguidas, y 3 veces seguidas, por lo que el máximo es 3.
template<std::size_t SIZE>
int Contiguous7(const std::array<int, SIZE> &arr) {
  std::size_t counter{0};
  std::size_t max{0};
  for (std::size_t i{0}; i < SIZE; ++i) {
    if (arr[i] == 7) {
      if (++counter > max) max = counter;
    } else {
      counter = 0;
    }
  }
  return max;
}

void Test() {
  std::array arr{1, 2, 7, 7, 4, 3, 3, 7, 7, 7, 2};
  assert(Contiguous7(arr) == 3);
  std::array<int, 0> arr_2{};
  assert(Contiguous7(arr_2) == 0);
  std::array arr_3{7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
  assert(Contiguous7(arr_3) == 10);
  std::array arr_4{1, 7, 2, 7, 7, 3, 7, 7, 7};
  assert(Contiguous7(arr_4) == 3);
}

int main() {
  // Test();
  std::array arr{1, 2, 7, 7, 4, 3, 3, 7, 7, 7, 2};
  std::cout << "El numero 7 aparace como maximo " << Contiguous7(arr)
            << " veces seguidas.";
}