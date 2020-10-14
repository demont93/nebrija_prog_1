#include <cassert>
#include <iostream>
#include <array>
#include "user_io.h"
#include "utilities.h"

// Crear un std::array de 10 elementos que contenga los 10 primeros números de
// la Serie de Fibonacci. Los números se deben calcular, no introducir uno a
// uno. Sólo se pueden introducir manualmente los dos primeros.

void FillFibTable(std::array<int, 10> &table) {
  assert(table[0] == 0 && table[1] == 1 &&
         "Array passed to MakeFib must have index 0 and 1 set");
  auto it {table.begin() + 2};
  auto end{table.end()};
  while (it != end) {
    *it = *(it - 1) + *(it - 2);
    ++it;
  }
}

void Test() {
  std::array<int, 10> correct{0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
  std::array<int, 10> empty{0, 1};
  assert(correct != empty);
  FillFibTable(empty);
  assert(correct == empty);
}

int main() {
  // Test();
  UserIO io{};
  std::array<int, 10> empty{0, 1};

  io << "Esta es la tabla vacia:\n"
     << CollectionString(empty.begin(), empty.end()) << '\n';
  FillFibTable(empty);
  io << "Esta es la tabla llena:\n"
     << CollectionString(empty.begin(), empty.end()) << '\n';
}