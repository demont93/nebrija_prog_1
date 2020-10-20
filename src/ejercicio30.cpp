//===-- ejercicio30.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio30
/// -----------
/// Crear una función que recorra un vector de números enteros positivos y
/// devuelva un vector con aquellos números que sean primos. Para ello se creará
/// previamente una función que diga si un número es primo o no.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT
#include <cassert>
#include <algorithm>
#include <vector>
#include <any>
#include <cmath>
#include "doctest.h"

// Crea la mitad de abajo de el "Sieve of Erathosthenes" para un numero n.
std::vector<int> Sieve(int for_n) {
  assert(for_n > 0 && "Cant compute a sieve for a number of 0 or less");

  // Creamos el sieve suponiendo que todos son primos y vamos descartando todos
  // los multiplos de los primos que vayamos obteniendo.
  std::vector<bool> sieve(std::sqrt(for_n) + 1, true);
  sieve[0] = false; // 0 y 1 no son primos por definicion
  sieve[1] = false;

  // Vamos recorriendo el array buscando primos para descartar elementos del
  // sieve.
  std::size_t cursor{2};
  std::size_t max_possible_cursor{static_cast<size_t>(std::sqrt(sieve.size()))};
  while (cursor <= max_possible_cursor) {
    if (sieve[cursor]) {
      for (std::size_t i{cursor * 2}, e{sieve.size()}; i < e; i += cursor)
        sieve[i] = false;
    }
    ++cursor;
  }

  // Creamos un vector para almacenar los primos (los indices con valor true en
  // el vector _sieve_).
  std::vector<int> primes{};
  primes.reserve(max_possible_cursor);
  for (std::size_t i{0}; i < sieve.size(); ++i)
    if (sieve[i]) primes.push_back(i);
  return primes;
}

// Hace check contra el sieve para ver si el numero es divisible por algun otro
// mas que el mismo y 1.
bool IsPrime(int n) {
  assert(n >= 0 && "IsPrime should not have a negative parameter.");
  if (n == 0 || n == 1) return false;
  std::vector<int> sieve{Sieve(n)};
  bool is_prime{true};
  for (const int &prime : sieve) {
    if (n % prime == 0) {
      is_prime = false;
      break;
    }
  }
  return is_prime;
}

std::vector<int> TakePrimes(const std::vector<int> &numbers) {
  assert(std::all_of(numbers.begin(), numbers.end(),
                     [](const int &n) { return n >= 0; }));
  std::vector<int> primes{};
  for (const int &n : numbers)
    if (IsPrime(n)) primes.push_back(n);
  return primes;
}

void Test() {
  std::vector v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  assert(TakePrimes(v) == (std::vector<int>{2, 3, 5, 7, 11, 13}));
}

int main() {
  // TODO
  Test();
}