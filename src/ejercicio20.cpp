//===-- ejercicio20.cpp -----------------------------------------*- C++ -*-===//
//
// Ejercicio20
// Pedir al usuario que introduzca una cadena de texto por teclado, almacenarla
// en un std::string, crear a continuación un std::vector que contenga cada una
// de las palabras de la cadena por separado.
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <iostream>
#include <vector>
#include "utilities.h"
#include "user_io.h"

std::vector<std::string> StringToWordVector(const std::string &sentence) {
  constexpr const char k_space_char = ' ';
  std::vector<std::string> words{};
  std::string one_word{};

  std::size_t i{0};
  std::size_t end{sentence.size()};
  while (i < end) {                                   // hasta finalizar string
    if (sentence[i] == k_space_char) {                // si es espacio
      ++i;                                            // ignora 1
      while (i < end && sentence[i] == k_space_char)  // y mientras sea espacio
        ++i;                                          // sigue ignorando 1
    } else {                                          // de lo contrario
      one_word.push_back(sentence[i++]);              // anade un char a palabra
      while (i < end && sentence[i] != k_space_char)  // mientras no sea espacio
        one_word.push_back(sentence[i++]);            // sigue anadiendo chars
      words.push_back(one_word);                      // anade la palabra al vec
      one_word.clear();                               // resetea la palabra
    }
  }
  return words;                                       // devolvemos el resultado
}

void Test() {
  using words = std::vector<std::string>;
  assert(StringToWordVector("").empty());
  assert(StringToWordVector("hola") == words{"hola"});
  assert(StringToWordVector("frobnicate THE scROGnate") ==
         (words{"frobnicate", "THE", "scROGnate"}));
  assert(StringToWordVector("          much space comma          ") ==
         (words{"much", "space", "comma"}));
  assert(StringToWordVector("                                       ").empty());
  assert(StringToWordVector("                                  d") ==
         words{"d"});
}

int main() {
  // Test();
  UserIO io{};
  io << "Introduce una oracion: \n";
  if (!io.GetInputFromUser()) return 0;
  std::string s;
  io.GetLine(s);
  std::vector<std::string> words {StringToWordVector(s)};
  io << "Palabras sin espacio:\n"
     << CollectionString(words.begin(), words.end())
     << '\n';
}