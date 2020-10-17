//===-- ejercicio7.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio7
// Pedir al usuario que introduzca un texto por teclado y mostrar por pantalla
// el número de veces que aparece la vocal "a".
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cassert>
#include "utilities.h"
#include "user_io.h"

// Busqueda lineal con range loop.
int TimesA(const std::string &s) {
  int counter{0};
  // Usamos un const char para asegurarnos de no cambiarlo.
  // Usamos referencia _&c_ para no copiar el char en cada iteracion
  for (const char &c : s)
    if (c == 'a' || c == 'A') ++counter;
  return counter;
}

void Test() {
  assert(TimesA("") == 0);
  assert(TimesA("10aaaaaaAaaa") == 10);
  assert(TimesA("0") == 0);
  assert(TimesA("Es la unica culpikeubo, la unica culpa que tengo.") == 5);
}

int main() {
  // Test();
  UserIO io;
  io << "Introduce una oracion preferiblemente con 'a' o 'A': ";
  std::string user_input{};
  if (!io.GetInputFromUser()) return 0;
  io.GetLine(user_input);
  io << "'A' or 'a' in text: " << TimesA(user_input) << '\n';
}