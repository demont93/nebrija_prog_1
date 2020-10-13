#include <iostream>
#include <array>

// Ejercicio6
// Realizar un programa que recorra un array de valores enteros y busque si
// contiene el número 7. En caso de que lo contenga imprimir por pantalla todas
// las posiciones en las que lo contiene.
template<std::size_t SIZE>
void PrintAllElemArray(const std::array<int, SIZE> &arr) {
  for (int i{0}; i < arr.size(); ++i) {
    if (arr[i] == 7) {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
}

int main() {
  std::array arr{1, 2, 3, 4, 5, 6, 7};
  PrintAllElemArray(arr);
  std::array arr_2{7, 0, 0, 0};
  PrintAllElemArray(arr_2);
  std::array arr_3{0, 0, 0, 0};
  PrintAllElemArray(arr_3);
  std::array arr_4{7, 7, 7, 7, 7, 7, 7, 7};
  PrintAllElemArray(arr_4);
}