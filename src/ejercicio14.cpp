//
// Created by callisto on 10/11/20.
//

#include <iostream>
#include <cassert>
#include <vector>
#include <utilities.h>

// Ejercicio14
// Usando `for elem:vec`. A partir de un vector de números enteros, crear otro
// que contenga sólo los números pares. Por ejemplo, a partir de {1,3,4,5,6,7}
// se crea -> {4,6}.
std::vector<int> Evens(const std::vector<int> &v) {
  std::vector<int> new_v{};
  for (const int &n : v) {
    if (n % 2 == 0) {
      new_v.push_back(n);
    }
  }
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
  std::cout << "A partir del vector ";
  std::vector given{1,3,4,5,6,7};
  PrintCollection(given.begin(), given.end());
  std::cout << ", sacamos los numeros pares: ";
  std::vector result{Evens(given)};
  PrintCollection(result.begin(), result.end());
  std::cout << std::endl;
}
