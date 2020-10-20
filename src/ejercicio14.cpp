//===-- ejercicio14.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio14
/// Usando `for elem:vec`. A partir de un vector de números enteros, crear otro
/// que contenga sólo los números pares. Por ejemplo, a partir de {1,3,4,5,6,7}
/// se crea -> {4,6}.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <vector>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

std::vector<int> Evens(const std::vector<int> &v) {
  std::vector<int> new_v{};
  for (const int &n : v)
    if (n % 2 == 0) new_v.push_back(n);
  return new_v;
}

TEST_CASE ("test Evens") {
  CHECK_EQ(Evens(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}),
           std::vector<int>{2, 4, 6, 8});
  CHECK(Evens(std::vector{1, 3, 5, 7, 9}).empty());
  std::vector all_evens{2, 4, 6, 8};
  assert(Evens(all_evens) == all_evens);
  assert(Evens(std::vector<int>{}).empty());
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
  std::vector given{1, 3, 4, 5, 6, 7};
  std::vector result{Evens(given)};
  io << "A partir del vector "
     << CollectionString(given.begin(), given.end())
     << ", sacamos los numeros pares: "
     << CollectionString(result.begin(), result.end()) << '\n';
  return res;
}