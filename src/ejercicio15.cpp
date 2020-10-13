#include <cassert>
#include <iostream>
#include <vector>
#include "utilities.h"

// Ejercicio15
// Usando `while`. A partir de un vector de números enteros, crear otro que contenga
// sólo los números pares. Por ejemplo, a partir de {1,3,4,5,6,7} se crea -> {4,6}.
std::vector<int> WhileEvens(const std::vector<int> &v) {
  std::vector<int> new_vec;
  std::size_t i{0};
  while (i < v.size()) {
    if (v[i] % 2 == 0) new_vec.push_back(v[i]);
    ++i;
  }
  return new_vec;
}
void Test() {
  std::vector<int> v_1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> res{2, 4, 6, 8};
  assert(WhileEvens(v_1) == res);
  assert(WhileEvens(std::vector{1,3,5,7,9}).empty());
  std::vector all_evens{2,4,6,8};
  assert(WhileEvens(all_evens) == all_evens);
  assert(WhileEvens(std::vector<int>{}).empty());
}

int main() {
  // Test();
  std::cout << "A partir del vector: ";
  std::vector given{1,3,4,5,6,7};
  PrintCollection(given.begin(), given.end());
  std::cout << ", sacamos los numeros pares: ";
  std::vector result{WhileEvens(given)};
  PrintCollection(result.begin(), result.end());
  std::cout << std::endl;
}