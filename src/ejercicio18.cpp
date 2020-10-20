//===-- ejercicio18.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio18
/// A partir de un vector de std::string crear otro vector que contenga sólo los
/// elementos que aparece después del std::string "guardar". Por ejemplo, para el
/// vector {"perro", "gato", "guardar", "andres", "luis", "guardar", "botella"}
/// crearía otro vector conteniendo {"andres", "botella"}.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <vector>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

constexpr const char *const kSaveWord{"guardar"};

std::vector<std::string>
ElemsAfterSave(const std::vector<std::string> &haystack) {
  std::vector<std::string> needles{};
  if (haystack.empty()) return needles;

  // Iteramos todos menos 1, no importa si el ultimo dice guardar
  for (std::size_t i{0}, e{haystack.size() - 1}; i < e; ++i) {
    if (haystack[i] == kSaveWord)
      needles.push_back(haystack.at(i + 1));
  }
  return needles;
}

TEST_CASE ("test ElemsAfterSave") {
  CHECK(ElemsAfterSave(std::vector<std::string>{}).empty());
  CHECK(ElemsAfterSave(std::vector<std::string>{"hola"}).empty());
  CHECK(ElemsAfterSave(std::vector<std::string>{"guardar"}).empty());
  CHECK_EQ(ElemsAfterSave(std::vector<std::string>{"guardar", "guardado"}),
           (std::vector<std::string>{"guardado"}));
  CHECK_EQ(ElemsAfterSave(
  std::vector<std::string>{"guardar", "guardar", "guardado"}),
           (std::vector<std::string>{"guardar", "guardado"}));
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
  std::vector<std::string> haystack{"cosas", "otras cosas", "Vegetarianos",
                                    "guardar", "carne", "cultura", "guardar",
                                    "reggaeton"};
  io << "A partir de la coleccion: \n"
     << CollectionString(haystack.begin(), haystack.end()) << '\n'
     << "guardaremos\n";
  std::vector<std::string> needles{ElemsAfterSave(haystack)};
  io << CollectionString(needles.begin(), needles.end()) << '\n';
  return res;
}