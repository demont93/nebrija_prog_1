#include <cmath>
#include <array>
#include <vector>
#include <cassert>
#include "utilities.h"
#include "user_io.h"

// Ejercicio19
// Pedir al usuario un número y mostrar por pantalla si dicho número es primo o
// no (usando el bucle while).

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
      for (std::size_t i{cursor * 2}, e{sieve.size()}; i < e; i += cursor) {
        sieve[i] = false;
      }
    }
    ++cursor;
  }

  // Creamos un vector para almacenar los primos (los indices con valor true en
  // el vector _sieve_).
  std::vector<int> primes{};
  primes.reserve(max_possible_cursor);
  for (std::size_t i{0}; i < sieve.size(); ++i) {
    if (sieve[i]) primes.push_back(i);
  }
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

void Test() {
  assert(Sieve(1).empty());
  assert(Sieve(2).empty());
  assert(Sieve(10) == (std::vector{2, 3}));
  assert(Sieve(34) == (std::vector{2, 3, 5}));

  assert(!IsPrime(0));
  assert(!IsPrime(1));
  assert(IsPrime(2));
  assert(!IsPrime(171));
  assert(IsPrime(197));
  assert(IsPrime(5387));
  assert(!IsPrime(4927));
}

int main() {
  // Test();
  UserIO io{};
  while (true) {
    try {
      int n;
      io << "Introduce un entero para saber si es primo: ";
      if (!io.GetInputFromUser()) return 0;

      io.Token(n);
      if (IsPrime(n)) {
        io << n << " es primo.\n";
      } else {
        io << n << " no es primo.\n";
      }
      return 0;
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}