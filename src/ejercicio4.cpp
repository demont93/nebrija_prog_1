//===-- ejercicio4.cpp ------------------------------------------*- C++ -*-===//
//
// Ejercicio4
// Pedir al usuario que introduzca un texto por teclado. Comprobar si el texto
// contiene la palabra "password" y en caso de que la contenga mostrar por
// pantalla la palabra que haya a continuación.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cassert>
#include "user_io.h"

// En este caso he decidido retornar un std::string en vez de imprimir directo
// a un stream debido a que podriamos reusar alguna de esta logica mas adelante.
std::string GetPassword(const std::string &s) {
  std::stringstream ss{s};
  std::string word{};
  while (ss >> word) { // extrae palabras hasta fallar
    if (word == "password") {
      if (ss >> word) return word; // si hay palabra despues de passwd, imprime
      else return "";
    }
  }
  return "";
}

void Test() {
  // Las pruebas que hagamos tienen que tratar de romper el programa. Es
  // importante volverse experto rompiendo programas, ya que es la mejor forma
  // de entrenarse para que tus trabajos sean solidos, libres de bugs, y
  // seguros.
  assert(GetPassword("").empty());
  assert(GetPassword("passwrd hjello1234").empty());
  assert(GetPassword("password 1234") == "1234");
  assert(GetPassword("lkdjf kd 3 aaa password big password small") == "big");
}

int main() {
  // Test();
  UserIO io;
  io << "No introduzcas una contrasena verdadera!\n"
     << "Introduce un texto y guardare la palabra despues de 'password': ";
  std::string user_input;
  // GetInputFromUser tiene la anotacion [[nodiscard]] la cual significa que si
  // descartamos el retorno de la funcion, el compilador nos dara una
  // advertencia.
  if (!io.GetInputFromUser()) return 0;
  io.GetLine(user_input);
  // La razon por la cual utilizo el '\n' en vez de std::endl es porque endl,
  // ademas de hacer un newline, tambien invoca un flush(). Muchas veces no
  // buscamos este comportamiento, pero lo introducimos sin darnos cuenta.
  io << "La palabra guardada fue: " << GetPassword(user_input) << '\n';
}