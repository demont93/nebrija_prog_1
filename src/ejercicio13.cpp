//
// Created by callisto on 10/11/20.
//

#include <cassert>
#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <utilities.h>

// Ejercicio13
// Pedir al usuario que introduzca un texto por teclado y mostrar todas las
// palabras que contengan al menos una "a".
std::vector<std::string> ContainsA(const std::string &s) {
  std::stringstream ss{s};
  std::string word{};
  std::vector<std::string> words_with_a{};
  while (ss >> word) {
    if (word.find_first_of("aA") != std::string::npos) {
      words_with_a.push_back(word);
    }
  }
  return words_with_a;
}

void Test() {
  assert(ContainsA("This text contains 3 words with an 'A'") ==
         (std::vector<std::string>{"contains", "an", "'A'"}));
  assert(ContainsA("").empty());
  assert(ContainsA("aaaaaaaaaaaaaaaaaaaaaa") ==
         std::vector<std::string>{"aaaaaaaaaaaaaaaaaaaaaa"});
}

int main() {
  // Test();
  std::string user_input{};
  std::cout << "Introduzca un texto: ";
  getline(std::cin, user_input);
  std::cout << "Estas palabras contienen 'a' o 'A': ";
  std::vector result{ContainsA(user_input)};
  PrintCollection(result.begin(), result.end());
  std::cout << std::endl;
}