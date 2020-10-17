//===-- ejercicio13.cpp -----------------------------------------*- C++ -*-===//
//
// Ejercicio13
// Pedir al usuario que introduzca un texto por teclado y mostrar todas las
// palabras que contengan al menos una "a".
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <array>
#include <vector>
#include "utilities.h"
#include "user_io.h"

std::vector<std::string> ContainsA(const std::string &s) {
  std::stringstream ss{s};
  std::string word{};
  std::vector<std::string> words_with_a{};
  while (ss >> word) {
    if (word.find_first_of("aA") != std::string::npos)
      words_with_a.push_back(word);
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
  UserIO io;
  std::string user_input{};
  io << "Introduzca un texto: ";
  if (!io.GetInputFromUser()) return 0;
  io.GetLine(user_input);
  io << "Estas palabras contienen 'a' o 'A': ";
  std::vector result{ContainsA(user_input)};
  io << CollectionString(result.begin(), result.end()) << '\n';
}