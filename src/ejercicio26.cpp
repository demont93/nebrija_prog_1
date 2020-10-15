#include <cassert>
#include <algorithm>
#include <chrono>
#include <vector>
#include <array>
#include <random>
#include "utilities.h"
#include "user_io.h"

// A partir de un array de 100 números enteros aleatorios entre 0 y 20 (ver cómo
// generar números aleatorios), guardar en el tipo de dato pertinente todos
// aquellos que sean múltiplos de 3 y posteriormente imprimirlos por pantalla
// (no se debe repetir ninguno).


void FillRandom(std::array<int, 100> &randoms) {
  auto seed{
    static_cast<unsigned int>(std::chrono::high_resolution_clock::now()
      .time_since_epoch()
      .count())};
  std::default_random_engine gen(seed);
  std::uniform_int_distribution<int> distribution(0, 20);
  for (auto &i : randoms)
    i = distribution(gen);
}

std::vector<int> PseudoRandomMultiplesOf3(std::array<int, 100> &randoms) {
  std::array<int, 20> table{};
  for (size_t i{3}, e{table.size()}; i < e; i += 3)
    table[i] = true;
  for (const auto &n : randoms)
    table[n] = false;
  std::vector<int> result;
  result.reserve(6);
  for (size_t i{3}, e{table.size()}; i < e; i += 3) {
    if (!table[i])
      result.push_back(i);
  }
  return result;
}

void Test() {
  {
    std::array<int, 100> table{};
    FillRandom(table);
    std::array<int, 100> table_2{};;
    FillRandom(table_2);
    assert(table != table_2);
  }
  {
    std::array<int, 100> table{};
    table[50] = 3;
    table[0] = 6;
    table[5] = 9;
    table[98] = 3;
    assert(PseudoRandomMultiplesOf3(table) == (std::vector<int>{3, 6, 9}));
  }
  {
    std::array<int, 100> all_zero{};
    assert(PseudoRandomMultiplesOf3(all_zero).empty());
  }
  {
    std::array<int,100> all_three{};
    all_three.fill(3);
    assert(PseudoRandomMultiplesOf3(all_three) == std::vector<int>{3});
  }
}

int main() {
  // Test();
  UserIO io;
  std::array<int, 100> table{};
  FillRandom(table);
  io << "A partir del array "
     << CollectionString(table.begin(), table.end())
     << " obtenemos los multiplos de 3:\n";
  std::vector<int> result{PseudoRandomMultiplesOf3(table)};
  io << CollectionString(result.begin(), result.end()) << '\n';
}