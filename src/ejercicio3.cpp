//===-- ejercicio3.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio3
// A partir del texto "En un lugar de la Mancha, de cuyo nombre no quiero
// acordarme" crear un programa que muestre por pantalla dos textos: lo que hay
// antes de Mancha (En un lugar de la ) y lo que hay después (, de cuyo nombre
// no quiero acordarme).
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cassert>
#include "user_io.h"

constexpr const char *const kPhrase{
  "En un lugar de la Mancha, de cuyo nombre no quiero acordarme"};

template<typename T>
void BeforeAfterMancha(T &output) {
  // En una declaracion _*_ declara un puntero, en un valor _*_ accede al valor
  // al cual apunta el puntero.
  const char *cursor{kPhrase};       // declara puntero a un char de la cadena
  while (*cursor != 'M') {           // movemos el cursor hasta encontrar M
    output << *cursor;               // _*_ accede a la memoria en el puntero
    ++cursor;
  }
  while (*cursor != ',') ++cursor;  // movemos el cursor hasta encontrar la coma
  output << cursor << '\n';         // imprimimos el resto de la cadena
}                                   // empezando por el cursor

void Test() {
  std::stringstream ss;
  BeforeAfterMancha(ss);
  assert(
    ss.str() == "En un lugar de la , de cuyo nombre no quiero acordarme\n");
}

int main() {
  // Test();
  UserIO io;
  io << "Si quitamos la palabra Mancha de: " << kPhrase << '\n'
     << "queda: ";
  BeforeAfterMancha(io);
}

