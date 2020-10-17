//===-- ejercicio18.cpp -----------------------------------------*- C++ -*-===//
//
// Ejercicio18
// A partir de un vector de std::string crear otro vector que contenga sólo los
// elementos que aparece después del std::string "guardar". Por ejemplo, para el
// vector {"perro", "gato", "guardar", "andres", "luis", "guardar", "botella"}
// crearía otro vector conteniendo {"andres", "botella"}.
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <iostream>
#include <vector>
#include "utilities.h"
#include "user_io.h"

constexpr const char *const kSaveWord{"guardar"};

// Las palabras muy utilizadas en programacion ayudan a entender el codigo como
// needle and haystack (aguja y pajar). Tengo un vector de agujas y tengo un
// pajar. Cada vez que encuentro una aguja la guardo.
std::vector<std::string>
ElemsAfterSave(const std::vector<std::string> &haystack) {
  std::vector<std::string> needles{};
  // Iteramos todos menos 1, no importa si el ultimo dice guardar
  for (std::size_t i{0}, e{haystack.size() - 1}; i < e; ++i)
    if (haystack[i] == kSaveWord)
      needles.push_back(haystack.at(i + 1));
  return needles;
}

void Test() {
  assert(ElemsAfterSave(std::vector<std::string>{}).empty());
  assert(ElemsAfterSave(std::vector<std::string>{"hola"}).empty());
  assert(ElemsAfterSave(std::vector<std::string>{"guardar"}).empty());
  assert(ElemsAfterSave(std::vector<std::string>{"guardar", "guardado"}) ==
         (std::vector<std::string>{"guardado"}));
  assert(ElemsAfterSave(
    std::vector<std::string>{"guardar", "guardar", "guardado"}) ==
         (std::vector<std::string>{"guardar", "guardado"}));
}

int main() {
  // Test();
  UserIO io;
  std::vector<std::string> haystack{"cosas", "otras cosas", "Vegetarianos",
                                    "guardar", "carne", "lgtbq", "guardar",
                                    "pronombres"};
  io << "A partir de la coleccion: \n"
     << CollectionString(haystack.begin(), haystack.end()) << '\n'
     << "guardaremos\n";
  std::vector<std::string> needles{ElemsAfterSave(haystack)};
  io << CollectionString(needles.begin(), needles.end()) << '\n';
}
