//
// Created by demont93 on 10/10/20.
//

#include <iostream>
#include <cassert>
#include "utilities.h"

// Ejercicio7
// Pedir al usuario que introduzca un texto por teclado y mostrar por pantalla
// el número de veces que aparece la vocal "a".
int TimesA(const std::string &s) {
  std::stringstream ss{s};
  int counter{0};
  char c;

  // ss.get es mas rapido que ss >> para caracteres si no necesitas ignorar whitespace
  while (ss.get(c)) {
    if (c == 'a' || c == 'A') { // TODO 'a' or 'a' || 'A' ?
      ++counter;
    }
  }
  return counter;
}

void Test() {
  assert(TimesA("10aaaaaaAaaa") == 10);
  assert(TimesA("0") == 0);
  assert(TimesA("Es la unica culpikeubo, la unica culpa que tengo.") == 5);
}

int main() {
  // Test();
  std::cout << "Enter some text: ";
  std::string user_input{};
  getline(std::cin, user_input);
  std::cout << "'A' or 'a' in text: " << TimesA(user_input) << std::endl;
}