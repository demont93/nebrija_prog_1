//===-- ejercicio15.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio15
/// Usando `while`. A partir de un vector de números enteros, crear
/// otro que contenga sólo los números pares. Por ejemplo, a partir de
/// {1,3,4,5,6,7} se crea -> {4,6}.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <vector>
#include "utilities.h"
#include "user_io.h"
#include "doctest.h"

std::vector<int> WhileEvens(const std::vector<int> &v) {
  std::vector<int> new_vec;
  std::size_t i{0};
  while (i < v.size()) {
    if (v[i] % 2 == 0) new_vec.push_back(v[i]);
    ++i;
  }
  return new_vec;
}
TEST_CASE("test WhileEvens") {
  std::vector<int> v_1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> res{2, 4, 6, 8};
  CHECK_EQ(WhileEvens(v_1), res);
  CHECK(WhileEvens(std::vector{1,3,5,7,9}).empty());
  std::vector all_evens{2,4,6,8};
  CHECK_EQ(WhileEvens(all_evens), all_evens);
  CHECK(WhileEvens(std::vector<int>{}).empty());
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
  std::vector given{1,3,4,5,6,7};
  std::vector result{WhileEvens(given)};
  io << "A partir del vector: "
     << CollectionString(given.begin(), given.end())
     << ", sacamos los numeros pares: "
     << CollectionString(result.begin(), result.end()) << '\n';
  return res;
}