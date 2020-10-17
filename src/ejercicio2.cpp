//===-- ejercicio2.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio2
// Crear un programa que muestre por pantalla las tres posiciones en las que
// aparece el texto "tri" en el siguiente texto: "Tres tristes tigres comen
// trigo en un trigal"
//
//===----------------------------------------------------------------------===//

#include <ostream>
#include <cassert>
#include "user_io.h"

constexpr const char *const kPhrase{
  "Tres tristes tigres comen trigo en un trigal"};
constexpr const char *const kSubs{"tri"};

// Utilizamos un template para poder pasarle otros streams a nuestra funcion.
// De esa manera podemos probar que funciona sin tener que poner el input
// manualmente.
template<typename T>
void PositionOfTri(T &output) {
  static const std::string phrase{kPhrase};
  std::size_t position{0};
  while ((position = phrase.find(kSubs, position)) &&
         position != std::string::npos) {             // si encontramos el subs
    output << position << " ";                        // imprimimos
    ++position;                                       // preincremento de pos
  }
  output << '\n';                                     // nueva linea
}

void Test() {
  // Aqui le pasamos un stringstream en vez de un std::cout.
  std::stringstream ss;
  PositionOfTri(ss);
  // Podemos asegurarnos de que el output es lo que esperamos que sea.
  assert(ss.str() == "5 26 38 \n");
}

int main() {
  // Test();
  UserIO io;
  io << kPhrase << " contiene " << kSubs << " en las posiciones:\n";
  // Le pasamos un UserIO a la funcion para tener un metodo universal de hacer
  // I/O con nuestro usuario, si luego deseamos cambiar el metodo utilizado,
  // podemos cambiar solamente UserIO o extenderla para no modificar el codigo
  // actual.
  PositionOfTri(io);
}