//===-- ejercicio1.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio 1
/// ===========
/// Sea una escena como la de la figura. La escena tiene un cuadrado, un
/// triángulo (no tiene que ser equilatero) y uncírculo. Las dimensiones y las
/// posiciones de estas figuras en la escena pueden cambiar. Se pide, crear una
/// estructura que sea capaz de albergar toda la información necesaria para
/// definir la escena.
///
//===----------------------------------------------------------------------===//

#include "user_io.h"

struct Point {
  double x;
  double y;
};

struct Segment {
  Point p1;
  Point p2;
};

struct Triangle {
  Point p1;
  Point p2;
  Point p3;
};

struct Square {
  Point p1;
  Point p2;
};

struct Circle {
  Point center;
  double radius;
};
struct Scene {
  Triangle triangle;
  Square square;
  Circle circle;
};

int main() {
  UserIO io;
  io << "Podemos construir una escena.\n";
}