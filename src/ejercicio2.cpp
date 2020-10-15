//===-- ejercicio2.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio2
// Crear un programa que muestre por pantalla las tres posiciones en las que
// aparece el texto "tri" en el siguiente texto: "Tres tristes tigres comen
// trigo en un trigal"
//
//===----------------------------------------------------------------------===//

#include <iostream>

void PositionOfTri() {
  const std::string phrase{"Tres tristes tigres comen trigo en un trigal"};
  const char *const tri{"tri"};
  size_t position{0};
  while ((position = phrase.find(tri, position)) &&
         position != std::string::npos) {             // si encontramos el subs
    std::cout << position << " ";                     // imprimimos
    ++position;                                       // preincremento de pos
  }
  std::cout << '\n';                                  // nueva linea
}

int main() {
  PositionOfTri();
}