//===-- ejercicio16.cpp -----------------------------------------*- C++ -*-===//
//
// Ejercicio16
// Pedir un número al usuario y calcular el sumatorio desde 1 hasta dicho
// número.
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <stdexcept>
#include "user_io.h"

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

// La entrada de los usuarios es molesta de escribir. Debes suponer que el
// usuario puede hacer CUALQUIER COSA INESPERADA. Es decir, si hay algo que
// puede salir mal, va a salir mal. Debes que pensar en:
//    * El rango del input que pides.
//    * Como manejar los errores cuando se sale de dicho rango.
//    * Como se comportara tu programa. Debe cerrar o debe presentar un mensaje
//      de error y pedir una entrada nuevamente.
//    * Validar y sanear las entradas. Una entrada que no se sanea puede llevar
//      algunas veces a brechas de seguridad. Una entrada que no se valida puede
//      puede llevar a tu programa a un estado corrupto o peor... UNDEFINED
//      BEHAVIOR.
//    * Asegurarte de que puedes manejar el input del usuario en tus objetos y
//      funciones.
//    * El casting implicito de tipos puede hacer que pierdas precision en un
//      un numero, que pierdas digitos, que se resetee a 0 y empiece de nuevo,
//      undefined behavior y otras cosas interesantes.
int main() {
  // Test();
  UserIO io;
  int n;
  while (true) {
    try {
      io << "Introduce un numero n: ";
      if (!io.GetInputFromUser()) return 0;
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
    } // Si el error no es ninguno de estos, dejamos que el programa explote.
  }
}