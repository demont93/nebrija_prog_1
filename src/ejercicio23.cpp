#include <cassert>
#include <iostream>
#include "user_io.h"

// Realizar un programa que pida al usuario un número y muestre por pantalla su
// factorial.

std::int64_t Factorial(int n) {
  assert(n <= 20 && n >= 0);
  if (n == 0) return 1;

  std::int64_t accumulator{1};
  for (int i{1}; i <= n; ++i) {
    accumulator *= i;
  }
  return accumulator;
};

void Test() {
  assert(Factorial(0) == 1);
  assert(Factorial(1) == 1);
  assert(Factorial(20) == 2432902008176640000);
  assert(Factorial(10) == 3628800);
}

int main() {
  // Test();
  UserIO io{};
  while (true) {
    try {
      io << "Introduce un entero n tal que 0 <= n <= 20:\n";
      if (!io.GetInputFromUser()) return 0;
      int n;
      io.Token(n);
      if (n < 0 || n > 20) {
        io << "Debes introducir un numero entre [0, 20].\n";
        continue;
      } else {
        io << "Factorial de " << n << ": "
           << Factorial(n) << '\n';
        return 0;
      }
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}