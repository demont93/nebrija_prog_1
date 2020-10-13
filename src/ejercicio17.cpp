#include <cassert>
#include <vector>
#include <cmath>
#include "utilities.h"
#include "user_io.h"


// Ejercicio17
// Pedir tres números al usario: _a_, _b_ y _c_. Crear un vector que contenga
// todos los números múltiplos de _c_ que hay entre _a_ y _b_ (incluídos).
// Assume : a <= b
//          0 < a, b, c <= 2^31

std::vector<int> MultiplesOfBetween(int multiples_of, int from, int to) {
  assert(multiples_of > 0 && from > 0 && to > 0);
  assert(from <= to);

  std::vector<int> new_v{};

  // Empezamos por el primer multiplo >= _to_
  int multiple =
    std::ceil(from / static_cast<double>(multiples_of)) * multiples_of;
  while (multiple <= to) {
    new_v.push_back(multiple);
    multiple += multiples_of; // siguiente multiplo
  }
  return new_v;
}

void Test() {
  assert(MultiplesOfBetween(5, 10, 20) == (std::vector{10, 15, 20}));
  assert(MultiplesOfBetween(100, 50, 60).empty());
  assert(MultiplesOfBetween(1, 1000, 1002) == (std::vector{1000, 1001, 1002}));
}

int main() {
  // Test();
  UserIO io;

  while (true) {
    try {
      int a, b, c;
      io << "Introduce 3 \"a,b,c\" separados por espacios para recibir todos "
         << "los multiplos de \"c\" entre \"a\" y \"b\":\n";
      if (!io.GetInputFromUser()) return 0;
      io.Token(a);
      io.Token(b);
      io.Token(c);
      if (a > b) {
        io << "'a' no puede ser mayor a 'b'\n"
           << "Intenta de nuevo\n";
      } else if (a < 1 || b < 1 || c < 1) {
        io << "Ningun numero puede ser menor a 1\n"
           << "Intenta de nuevo\n";
      } else {
        std::vector result{MultiplesOfBetween(c, a, b)};
        io << CollectionString(result.begin(), result.end()) << '\n';
        return 0;
      }
    } catch (std::overflow_error &e) {
      io.Err(e.what());
      io.Err('\n');
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}