//
// Created by demont93 on 10/9/20.
//

#include <iostream>
#include <sstream>
#include <cassert>

// Ejercicio4
// Pedir al usuario que introduzca un texto por teclado. Comprobar si el texto
// contiene la palabra "password" y en caso de que la contenga mostrar por pantalla
// la palabra que haya a continuación.
std::string Password(const std::string &s) {
  std::stringstream ss{s};
  std::string word{};
  while (ss >> word) { // extract word until fail
    if (word == "password") {
      if (ss >> word) {
        return word; // if word after password, print
      } else {
        return "";
      }
    }
  }
  return "";
}

void Test() {
  assert(Password("").empty());
  assert(Password("passwrd hjello1234").empty());
  assert(Password("password 1234") == "1234");
  assert(Password("lkdjf kd 3 aaa password big password small") == "big");
}

int main() {
  // Test();
  std::cout << "Introduce un texto: ";
  std::string user_input;
  getline(std::cin, user_input);
  std::cout << Password(user_input) << std::endl;
}