#include <cassert>
#include <stdexcept>
#include "user_io.h"

// Ejercicio16
// Pedir un número al usuario y calcular el sumatorio desde 1 hasta dicho número.

constexpr int kMax{65535};

int Series(const int n) {
  assert(n >= 0 && n <= kMax);
  auto big_n = static_cast<std::int64_t>(n);
  return big_n * (big_n + 1) / 2.0;
}

void Test() {
  assert(Series(10) == 55);
  assert(Series(0) == 0);
  assert(Series(100) == 5050);
  assert(Series(65535) == 2147450880);
}

int main() {
  // Test();
  UserIO io;
  int n;
  while (true) {
    try {
      io << "Introduce un numero n: ";
      io.GetInputFromUser();
      io.Token(n);
      if (n > kMax || n < 0) {
        io << "El numero debe cumplir 0 >= n >= " << kMax << '\n';
      } else {
        io << "Sumatorio de 1 hasta " << n << ": " << Series(n) << '\n';
        return 0;
      }
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err("\n");
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err("\n");
    }
  }
}