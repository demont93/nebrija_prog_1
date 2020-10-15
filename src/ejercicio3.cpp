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

void BeforeAfterMancha() {
  const char *const phrase{
    "En un lugar de la Mancha, de cuyo nombre no quiero acordarme"};
  // En una declaracion _*_ declara un puntero, en un valor _*_ accede al valor
  // al cual apunta el puntero.
  const char *cursor{phrase};       // declara puntero a un char de la cadena
  while (*cursor != 'M') {          // movemos el cursor hasta encontrar M
    std::cout << *cursor;           // _*_ accede a la memoria en el puntero
    ++cursor;
  }
  while (*cursor != ',') ++cursor;  // movemos el cursor hasta encontrar la coma
  std::cout << cursor << '\n';      // imprimimos el resto de la cadena
}                                   // empezando por el cursor

int main() {
  BeforeAfterMancha();
}

