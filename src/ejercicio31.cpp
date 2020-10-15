#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>
#include "utilities.h"

// Ejercicio31
// Crear una función que devuelva un vector con los n primeros números primos.
// El número n se le debe pasar a la función como parámetro.

// Crea la mitad de abajo de el "Sieve of Erathosthenes" para un numero n.
std::vector<int> Sieve(int for_n) {
  assert(for_n > 0 && "Cant compute a sieve for a number of 0 or less");

  // Creamos el sieve suponiendo que todos son primos y vamos descartando todos
  // los multiplos de los primos que vayamos obteniendo.
  std::vector<bool> sieve(for_n + 1, true);
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

void Test() {
  assert(Sieve(14) == (std::vector<int> {2,3,5,7,11,13}));
  assert(Sieve(30) == (std::vector<int> {2,3,5,7,11,13,17,19,23,29}));
  assert(Sieve(2) == std::vector<int>{2});
}

int main() {
  Test();
}