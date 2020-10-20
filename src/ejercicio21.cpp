//===-- ejercicio21.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Crear un std::array de 10 elementos que contenga los 10 primeros números de
/// la Serie de Fibonacci. Los números se deben calcular, no introducir uno a
/// uno. Sólo se pueden introducir manualmente los dos primeros.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <array>
#include "user_io.h"
#include "utilities.h"
#include <utility>
#include "doctest.h"

/// Calcula Fibonacci durante compilacion
template<int T>
constexpr int Fib() {
  static_assert(T >= 0);
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

template<int ... I>
constexpr void
FibtabImpl(std::array<int, 10> &table, std::integer_sequence<int, I...>) {
  (..., (table[I] = Fib<I>()));
}

constexpr void FillFibTable(std::array<int, 10> &table) {
  FibtabImpl(table, std::make_integer_sequence<int, 10>{});
}

int main() {
  UserIO io{};
  std::array<int, 10> empty{};
  io << "Esta es la tabla vacia:\n"
     << CollectionString(empty.begin(), empty.end()) << '\n';
  FillFibTable(empty);
  io << "Esta es la tabla llena:\n"
     << CollectionString(empty.begin(), empty.end()) << '\n';
}