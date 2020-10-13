//
// Created by demont93 on 10/10/20.
//

#include <iostream>
#include <sstream>
#include <cassert>

// Ejercicio8
// Pedir al usuario que introduzca un texto por teclado y mostrar todas las
// palabras que empiecen por "a".
int TimesBeginA(
  const std::string &line) { // const para asegurarnos que no cambie el string
  std::stringstream ss{line}; // copiar a un stringstream
  int counter{0};
  std::string word{};
  while (ss >> word) { // sacar input hasta final de la linea
    if (word.front() == 'a' || word.front() == 'A') {
      ++counter;
    }
  }
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
//    Test();
  std::cout << "Introduce una linea de texto: ";
  std::string user_input{};
  getline(std::cin, user_input);
  std::cout << TimesBeginA(user_input) << std::endl;
}