//===-- ejercicio21.cpp -----------------------------------------*- C++ -*-===//
//
// Crear un std::array de 10 elementos que contenga los 10 primeros números de
// la Serie de Fibonacci. Los números se deben calcular, no introducir uno a
// uno. Sólo se pueden introducir manualmente los dos primeros.
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <array>
#include "user_io.h"
#include "utilities.h"
#include <utility>

template<int T>
constexpr int Fib() {
  return Fib<T - 1>() + Fib<T - 2>();
}

template<>
constexpr int Fib<0>() {
  return 0;
}

template<>
constexpr int Fib<1>() {
  return 1;
}

template <int ... I>
constexpr void fibtab_impl(std::array<int,10>& table, std::integer_sequence<int, I...>) {
  (..., (table[I] = Fib<I>()));
}

constexpr void fibtab(std::array<int,10> &table) {
  fibtab_impl(table, std::make_integer_sequence<int, 10>{});
}

void FillFibTable(std::array<int, 10> &table) {
  assert(table[0] == 0 && table[1] == 1 &&
         "Array passed to MakeFib must have index 0 and 1 set");
  auto it{table.begin() + 2};
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
  std::array<int, 10> empty{};
  io << "Esta es la tabla vacia:\n"
     << CollectionString(empty.begin(), empty.end()) << '\n';
  // FillFibTable(empty);
  fibtab(empty);
  io << "Esta es la tabla llena:\n"
     << CollectionString(empty.begin(), empty.end()) << '\n';
}