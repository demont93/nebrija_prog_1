//===-- ejercicio4.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio4
// Pedir al usuario que introduzca un texto por teclado. Comprobar si el texto
// contiene la palabra "password" y en caso de que la contenga mostrar por
// pantalla la palabra que haya a continuación.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <sstream>
#include <cassert>

std::string GetPassword(const std::string &s) {
  std::stringstream ss{s};
  std::string word{};
  while (ss >> word) { // extrae palabras hasta fallar
    if (word == "password") {
      if (ss >> word) return word; // si hay palabra despues de passwd, imprime
      else return "";
    }
  }
  return "";
}

void Test() {
  assert(GetPassword("").empty());
  assert(GetPassword("passwrd hjello1234").empty());
  assert(GetPassword("password 1234") == "1234");
  assert(GetPassword("lkdjf kd 3 aaa password big password small") == "big");
}

int main() {
  // Test();
  std::cout << "Introduce un texto: ";
  std::string user_input;
  getline(std::cin, user_input);
  std::cout << GetPassword(user_input) << std::endl;
}