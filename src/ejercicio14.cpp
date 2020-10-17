//===-- ejercicio14.cpp -----------------------------------------*- C++ -*-===//
//
// Ejercicio14
// Usando `for elem:vec`. A partir de un vector de números enteros, crear otro
// que contenga sólo los números pares. Por ejemplo, a partir de {1,3,4,5,6,7}
// se crea -> {4,6}.
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <vector>
#include "utilities.h"
#include "user_io.h"

std::vector<int> Evens(const std::vector<int> &v) {
  std::vector<int> new_v{};
  for (const int &n : v)
    if (n % 2 == 0) new_v.push_back(n);
  return new_v;
}

void Test() {
  std::vector<int> v_1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> res{2, 4, 6, 8};
  assert(Evens(v_1) == res);
  assert(Evens(std::vector{1,3,5,7,9}).empty());
  std::vector all_evens{2,4,6,8};
  assert(Evens(all_evens) == all_evens);
  assert(Evens(std::vector<int>{}).empty());
}

int main() {
  // Test();
  UserIO io;
  std::vector given{1,3,4,5,6,7};
  std::vector result{Evens(given)};
  io << "A partir del vector "
     << CollectionString(given.begin(), given.end())
     << ", sacamos los numeros pares: "
     << CollectionString(result.begin(), result.end()) << '\n';
}
