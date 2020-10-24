//===-- ejercicio37.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio37
/// ===========
/// Programa que pida al usuario el número del cual quiere visualizar su tabla
/// de multiplicar.
/// Restriccion: Tablas [1,10], 1 <= n <= 100
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "user_io.h"

struct MultTable {
  const int n;
  const std::vector<int> table;
};

MultTable MakeMultTable(const int n) {
  std::vector<int> table;
  table.reserve(10);
  for (int i{1}; i <= 10; ++i)
    table.push_back(n * i);
  return MultTable{n, std::move(table)};
}

template<typename T>
void PrintFormatted(const MultTable &table, T &output) {
  output << "\nTabla de multiplicar de " << table.n << " del 1 al 10\n"
         << "================================================\n";
  for (int i{0}; i < table.table.size(); ++i)
    output << table.n << " x " << i + 1 << " = " << table.table[i] << '\n';
}

TEST_CASE ("") {
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
  io << "Introduce un numero del 1 al 100: ";
  if (!io.GetInputFromUser()) return res;
  int user_input;
  io.Token(user_input);
  const auto m{MakeMultTable(user_input)};
  PrintFormatted(m, io);

  return res;
}