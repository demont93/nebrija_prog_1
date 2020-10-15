#include <cmath>
#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>
#include "user_io.h"
#include "utilities.h"

// Realizar un programa que pida al usuario un número y almacene en un
// std::vector sus factores (todos aquellos números menores que él por los que
// puede ser dividido).

void MaybePush1(int64_t n,
                std::vector<std::int64_t> &first_half_factors);

std::vector<int64_t>
CatReverseVector(std::vector<std::int64_t> &&first_half_factors,
                 std::vector<std::int64_t> &&second_half_factors);

void GetFactors(int64_t n, int64_t max,
                std::vector<std::int64_t> &second_half_factors,
                std::vector<std::int64_t> &first_half_factors);

void MaybePushMax(int64_t n, int64_t max,
                  std::vector<std::int64_t> &second_half_factors,
                  std::vector<std::int64_t> &first_half_factors);

std::vector<std::int64_t> Factors(std::int64_t n) {
  assert(n > 0 && "Cant output infinite factors of 0");

  // Como encontramos dos factores de un numero cada vez que encontramos un
  // numero divisible, inicializamos dos vectores: uno para cada mitad.
  // Podriamos meter todos los numeros en el mismo vector pero no quedaria
  // ordenado.
  std::vector<std::int64_t> first_half_factors{};
  std::vector<std::int64_t> second_half_factors{};
  // _max_ representa el maximo numero que tenemos que probar para evitar
  // repetir factores. Por ejemplo, si encontramos que 2 es un factor de 40, no
  // queremos probar el 20.
  std::int64_t max{  // truncado
    static_cast<std::int64_t>(std::sqrt(static_cast<long double>(n)))};

  MaybePush1(n, first_half_factors);
  GetFactors(n, max, second_half_factors, first_half_factors);
  MaybePushMax(n, max, second_half_factors, first_half_factors);

  return CatReverseVector(std::move(first_half_factors),
                          std::move(second_half_factors));
}

// Revisamos si hay que meter el uno ya que el problema dice que solo los
// factores menores a n.
inline void
MaybePush1(int64_t n, std::vector<std::int64_t> &first_half_factors) {
  if (1 < n)
    first_half_factors.push_back(1);
}

// Queremos concatenar los dos vectores para retornar uno, pero el segundo esta
// al reves. Copiamos el segundo vector al final del primero de atras para
// adelante. Ejemplo  v1 = 1 2 3 4 5, v2 = 10 9 8 7 6
//           Resultado v3 = 1 2 3 4 5 6 7 8 9 10
std::vector<int64_t>
CatReverseVector(std::vector<std::int64_t> &&first_half_factors,
                 std::vector<std::int64_t> &&second_half_factors) {
  std::copy(second_half_factors.rbegin(), second_half_factors.rend(),
            std::back_inserter(first_half_factors));
  return first_half_factors;
}

// Para cada numero divisible metemos el numero bajo en el primer vector y el
// numero alto en el segundo vector.
void GetFactors(int64_t n, int64_t max,
                std::vector<std::int64_t> &second_half_factors,
                std::vector<std::int64_t> &first_half_factors) {
  for (int64_t i{2}; i < max; ++i) {
    if (n % i == 0) {
      first_half_factors.push_back(i);
      second_half_factors.push_back(n / i);
    }
  }
}

// Para el maximo probamos si es divisible, de serlo, tenemos que asegurarnos
// de que no metamos el mismo numero dos veces. Ejemplo: 3 x 3 son factores de
// 9 pero no queremos meter el 3 dos veces.
void MaybePushMax(int64_t n, int64_t max,
                  std::vector<std::int64_t> &second_half_factors,
                  std::vector<std::int64_t> &first_half_factors) {
  if (n % max == 0 && max != 1) {
    first_half_factors.push_back(max);
    int64_t upper_factor{n / max};
    if (upper_factor != max)
      second_half_factors.push_back(upper_factor);
  }
}

void Test() {
  using longvec = std::vector<std::int64_t>;
  assert(Factors(1).empty());
  assert(Factors(2) == longvec{1});
  assert(Factors(10) == (longvec{1, 2, 5}));
  assert(Factors(32) == (longvec{1, 2, 4, 8, 16}));
  assert(Factors(29) == longvec{1});
}

int main() {
  UserIO io{};
  while (true) {
    try {
      io << "Introduce un entero n tal que 0 < n < 2^63:\n";
      if (!io.GetInputFromUser()) return 0;
      std::int64_t n;
      io.Token(n);
      if (n <= 0) {
        io << "Debes introducir un numero entre mayor a 0.\n";
        continue;
      } else {
        std::vector<std::int64_t> factors{Factors(n)};
        io << "Los factores de " << n << " son: "
           << CollectionString(factors.begin(), factors.end()) << '\n';
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