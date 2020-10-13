//
// Created by demont93 on 10/9/20.
//

#include <iostream>

// Ejercicio3
// A partir del texto "En un lugar de la Mancha, de cuyo nombre no quiero
// acordarme" crear un programa que muestre por pantalla dos textos: lo que hay
// antes de Mancha (En un lugar de la ) y lo que hay después (, de cuyo nombre
// no quiero acordarme).
void BeforeAfter() {
  const char *const phrase{
    "En un lugar de la Mancha, de cuyo nombre no quiero acordarme"};
  const char *cursor{phrase};
  while (*cursor != 'M') {
    std::cout << *cursor;
    ++cursor;
  }
  while (*cursor != ',') ++cursor;
  std::cout << cursor << std::endl;
}

int main() {
  BeforeAfter();
}

