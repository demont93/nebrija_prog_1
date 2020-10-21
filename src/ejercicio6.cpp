//===-- ejercicio6.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio6
/// ----------
/// Realizar un programa que recorra un array de valores enteros y busque si
/// contiene el número 7. En caso de que lo contenga imprimir por pantalla todas
/// las posiciones en las que lo contiene.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include <array>
#include <sstream>
#include "user_io.h"
#include "doctest.h"
#include "utilities.h"

template<std::size_t SIZE, typename T>
void PrintAllPositionsOf7(const std::array<int, SIZE> &arr, T &output) {
  for (int i{0}; i < SIZE; ++i)
    if (arr[i] == 7) output << i << " ";
  output << '\n';
}

TEST_SUITE ("test PrintAllPositionsOf7") {
TEST_CASE ("print newline if no 7") {
  std::stringstream ss;
  REQUIRE_EQ(ss.str(), "");
  SUBCASE("no elements in array") {
    std::array<int, 0> arr{};
    PrintAllPositionsOf7(arr, ss);
    CHECK_EQ(ss.str(), "\n");
  }
  SUBCASE("no element 7 in array") {
    std::array arr{3,42,0,2,1,9};
    PrintAllPositionsOf7(arr,ss);
    CHECK_EQ(ss.str(), "\n");
  }
}
TEST_CASE ("print position of one seven") {
  std::stringstream ss;
  SUBCASE("print position if only 1 seven") {
    std::array arr{7};
    PrintAllPositionsOf7(arr, ss);
    CHECK_EQ(ss.str(), "0 \n");
  }
  SUBCASE("print position if 1 seven and other numbers") {
    std::array arr{1,0,7,0,0,0,0,0,0,9};
    PrintAllPositionsOf7(arr, ss);
    CHECK_EQ(ss.str(), "2 \n");
  }
}
TEST_CASE("print position of many 7s") {
  std::stringstream ss;
  std::array arr{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7};
  PrintAllPositionsOf7(arr,ss);
  CHECK_EQ(ss.str(), "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 \n");
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
  std::array arr{7, 7, 7, 7, 7, 7, 7, 7};
  io << "En el siguiente array:\n" << CollectionString(arr.begin(), arr.end())
     << "\nhemos encontrado el 7 en las posiciones: \n";
  PrintAllPositionsOf7(arr, io);
  io << '\n';
  return res;
}