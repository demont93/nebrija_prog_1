#include <vector>
#include <cassert>
#include <iostream>

// Crear una función que reciba como parámetros una frase y un caracter
// "separado" y devuelva un vector con cada uno de los elemtos separados. Por
// ejemplo, si le pasamos la frase "www.nebrija.es" y como elemento separado el
// caracter '.', devolverá el vector {"www", "nebrija", "es"}.

std::vector<std::string>
SplitDelim(const std::string &phrase, char delimiter) {
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
  if (!one_word.empty())
    words.push_back(one_word);
  return words;
}

void Test() {
  using wordvec = std::vector<std::string>;
  assert(
    SplitDelim("www.nebrija.es", '.') == (wordvec{"www", "nebrija", "es"}));
}

int main() {
  // TODO
  Test();
}