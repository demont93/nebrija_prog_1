//===-- ejercicio29.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejerjcicio29
/// ------------
/// Crear una función que reciba como parámetros una frase y un caracter
/// "separado" y devuelva un vector con cada uno de los elemtos separados. Por
/// ejemplo, si le pasamos la frase "www.nebrija.es" y como elemento separado el
/// caracter '.', devolverá el vector {"www", "nebrija", "es"}.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <vector>
#include <iostream>
#include "doctest.h"
#include "user_io.h"
#include "utilities.h"

std::vector<std::string> SplitDelim(const std::string &phrase, char delimiter) {
  std::string one_word{};
  std::vector<std::string> words{};
  for (const char &c : phrase) {
    if (c == delimiter) {
      words.push_back(one_word);
      one_word.clear();
    } else {
      one_word.push_back(c);
    }
  }
  words.push_back(one_word);
  return words;
}

TEST_CASE ("test SplitDelim") {
  using wordvec = std::vector<std::string>;
    CHECK_EQ(SplitDelim("www.nebrija.es", '.'),
             (wordvec{"www", "nebrija", "es"}));
    CHECK_EQ(SplitDelim(",,,", ','), wordvec{"", "", "", ""});
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;

  UserIO io;
  io << "Escribe una frase:\n";
  if (!io.GetInputFromUser()) return res;
  std::string line;
  io.GetLine(line);;
  io << "Escribe un caracter separador (ASCII), solo tomare el primero: \n";
  if (!io.GetInputFromUser()) return res;
  std::string separators;
  io.GetLine(separators);
  char c = separators[0];
  std::vector<std::string> result{SplitDelim(line, c)};
  io << CollectionString(result.begin(), result.end()) << '\n';
  return res;
}