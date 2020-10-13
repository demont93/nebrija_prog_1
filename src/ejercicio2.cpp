#include <cstring>
#include <iostream>

// Ejercicio2
// Crear un programa que muestre por pantalla las tres posiciones en las que aparece
// el texto "tri" en el siguiente texto: "Tres tristes tigres comen trigo en un trigal"
void PosOfTri() {
  const std::string phrase{"Tres tristes tigres comen trigo en un trigal"};
  const char *const tri{"tri"};
  size_t position{0};
  while ((position = phrase.find(tri, position)) &&
         position != std::string::npos) {
    std::cout << position << " ";
    ++position;
  }
  std::cout << std::endl;
}

int main() {
  PosOfTri();
}