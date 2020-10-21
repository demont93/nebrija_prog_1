//===-- ejercicio26.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio26
/// -----------
/// A partir de un array de 100 números enteros aleatorios entre 0 y 20 (ver
/// cómo generar números aleatorios), guardar en el tipo de dato pertinente
/// todos aquellos que sean múltiplos de 3 y posteriormente imprimirlos por
/// pantalla (no se debe repetir ninguno).
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <algorithm>
#include <chrono>
#include <vector>
#include <array>
#include <random>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

/// Llena un array de 100 enteros con numeros al azar de [0,20] de acuerdo a
/// std::uniform_int_distribution
/// @param [out] randoms Array donde se guardan los numero al azar.
void FillRandom(std::array<int, 100> &randoms) {
  auto seed{static_cast<unsigned int>(std::chrono::high_resolution_clock::now()
    .time_since_epoch()
    .count())};
  std::default_random_engine gen(seed);
  std::uniform_int_distribution<int> distribution(0, 20);
  for (auto &i : randoms)
    i = distribution(gen);
}

std::vector<int> MultiplesOf3(const std::array<int, 100> &randoms) {
  // Usamos una tabla para guardar los multiplos unicos en orden.
  std::array<int, 20> table{};
  for (int i{3}, e{table.size()}; i < e; i += 3)
    table[i] = true;
  for (const auto &n : randoms)
    table[n] = false;
  std::vector<int> result;
  result.reserve(6);
  for (int i{3}, e{table.size()}; i < e; i += 3) {
    if (!table[i])
      result.push_back(i);
  }
  return result;
}

TEST_CASE ("test FillRandom") {
  std::array<int, 100> table{};
  FillRandom(table);
  std::array<int, 100> table_2{};
  FillRandom(table_2);
  CHECK_NE(table, table_2);
}

TEST_CASE ("test MultiplesOf3") {
  std::array<int, 100> table{};
    REQUIRE(
    std::all_of(table.begin(), table.end(), [](int &n) { return n == 0; }));
    SUBCASE("only multiples of 3") {
    table[50] = 3;
    table[0] = 6;
    table[5] = 9;
    table[98] = 3;
    CHECK_EQ(MultiplesOf3(table), (std::vector<int>{3, 6, 9}));
  }
  SUBCASE("all zero"){
    assert(MultiplesOf3(table).empty());
  }
  SUBCASE("all three"){
    table.fill(3);
    CHECK_EQ(MultiplesOf3(table), std::vector<int>{3});
  }
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
  std::array<int, 100> table{};
  FillRandom(table);
  io << "A partir del array "
     << CollectionString(table.begin(), table.end())
     << " obtenemos los multiplos de 3:\n";
  std::vector<int> result{MultiplesOf3(table)};
  io << CollectionString(result.begin(), result.end()) << '\n';
  return res;
}