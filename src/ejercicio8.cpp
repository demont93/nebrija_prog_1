//===-- ejercicio8.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio8
// Pedir al usuario que introduzca un texto por teclado y mostrar todas las
// palabras que empiecen por "a".
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cassert>
#include "user_io.h"

// Const para asegurarnos que no cambie el string.
int TimesBeginA(const std::string &line) {
  // Usamos un stringstream para poder sacar las palabras con _>>_.
  std::stringstream ss{line}; // copiar a un stringstream
  std::string word{};
  int counter{0};
  while (ss >> word)  // sacar input hasta final de la linea
    if (word.front() == 'a' || word.front() == 'A') ++counter;
  return counter;
}

void Test() {
  assert(TimesBeginA("None start 0 with letter-a") == 0);
  assert(TimesBeginA("All are A4 aaaaaaa") == 4);
  assert(TimesBeginA("Some start with a but just 1") == 1);
  assert(TimesBeginA("a a a a a A A A a a A a") == 12);
  assert(TimesBeginA("a a a a a a a a a a a a ") == 12);
  assert(TimesBeginA("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 1);
}

int main() {
  // Test();
  UserIO io;
  io << "Introduce una linea de texto: ";
  if (!io.GetInputFromUser()) return 0;
  std::string user_input{};
  io.GetLine(user_input);
  io << "Palabras que comienzan con 'a' o 'A': "
     <<TimesBeginA(user_input) << '\n';
}