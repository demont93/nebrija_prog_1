//===-- ejercicio4.cpp ------------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio4
/// ==========
/// Pedir al usuario que introduzca un texto por teclado. Comprobar si el texto
/// contiene la palabra "password" y en caso de que la contenga mostrar por
/// pantalla la palabra que haya a continuación.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cstring>
#include <iostream>
#include "user_io.h"
#include "doctest.h"

std::string GetPassword(const std::string &s) {
  char ss[s.size()+1];
  strcpy(ss, s.c_str());
  const char *delim{" \t\r\n\v\f"};
  const char *word{strtok(ss, delim)};
  while (word != nullptr) {
    if (strcmp(word, "password") == 0) {
      word = strtok(nullptr, " ");
      if (word != nullptr) return {word};
      else return {};
    }
    word = strtok(nullptr, " ");
  }
  return {};
}

TEST_CASE("test password") {
  CHECK(GetPassword("").empty());
  CHECK(GetPassword("passwrd hjello1234").empty());
  CHECK_EQ(GetPassword("password 1234"), "1234");
  CHECK_EQ(GetPassword("lkdjf kd 3 aaa password big password small"), "big");
  CHECK(GetPassword("apassword &&&&").empty());
}

int main(int argc, char **argv) {
  doctest::Context ctx;
  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);
  int res = ctx.run();
  if (ctx.shouldExit())
    return res;

  UserIO io;
  io << "No introduzcas una contrasena verdadera!\n"
     << "Introduce un texto y guardare la palabra despues de 'password': ";
  std::string user_input;
  if (!io.GetInputFromUser()) return 0;
  io.GetLine(user_input);
  std::string result{GetPassword(user_input)};
  if (result.empty()) io << "No se guardo ninguna palabra.\n";
  else io << "La palabra guardada fue: " << result << '\n';
  return res;
}