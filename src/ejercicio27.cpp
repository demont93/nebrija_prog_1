//===-- ejercicio27.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio27
/// -----------
/// A partir de un array de 20 numeros enteros aleatorios entre 0 y 100,
/// imprimirlos por pantalla de modo ordenado y sin que se repitan.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <array>
#include <vector>
#include "doctest.h"
#include "user_io.h"
#include "utilities.h"

std::vector<int> OrderedUnique(const std::array<int, 20> &arr) {
  std::array<int, 100> lookup_table{};
  for (const int &n : arr)
    lookup_table[n] = true;
  std::vector<int> ordered_unique{};
  ordered_unique.reserve(20);
  for (int i{0}, e{lookup_table.size()}; i < e; ++i)
    if (lookup_table[i]) ordered_unique.push_back(i);
  return ordered_unique;
}

TEST_CASE ("test OrderedUnique") {
  std::array<int, 20> table{};
  table[2] = 45;
  table[1] = 45;
  table[0] = 90;
    CHECK(OrderedUnique(table) == (std::vector<int>{0, 45, 90}));
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;

  UserIo io;
  std::array<int, 20> table{};
  FillRandomInts(table.begin(), table.end(), 0, 100);
  io << "A partir del array "
     << CollectionString(table.begin(), table.end())
     << " obtenemos los enteros unicos ordenados:\n";
  std::vector<int> result{OrderedUnique(table)};
  io << CollectionString(result.begin(), result.end()) << '\n';
  return res;
}
