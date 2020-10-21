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

#include <iostream>
#include <algorithm>
#include "user_io.h"
#include "doctest.h"

template<typename T, typename F>
inline bool LimitBehind(T current, T begin, F is_delim) {
  return current == begin || is_delim(*(current - 1));
}

template<typename T, typename F>
inline bool LimitInFront(T current, T end, size_t len, F is_delim) {
  return current + len == end || is_delim(*(current + len));
}

std::string GetPassword(const std::string &s) {
  static const char *pass{"password"};
  int pass_len{8};
  auto e{s.end()};
  auto it{std::search(s.begin(), e, pass, pass + pass_len)};
  bool is_word{LimitBehind(it, s.begin(), isspace) &&
               LimitInFront(it, e, pass_len, isspace)};
  if (is_word) {
    it += pass_len; // skip password
    auto save_begin{std::find_if_not(it, e, isspace)};
    auto save_end = std::find_if(save_begin, e, isspace);
    std::string result{};
    std::copy(save_begin, save_end, std::back_inserter(result));
    return result;
  } else {
    return {};
  }
}

TEST_CASE ("test password") {
    CHECK(GetPassword("").empty());
    CHECK(GetPassword("passwrd hjello1234").empty());
    CHECK_EQ(GetPassword("password 1234"), "1234");
    CHECK_EQ(GetPassword("lkdjf kd 3 aaa password big password small"), "big");
    CHECK(GetPassword("hellomotto wr password").empty());
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

  UserIo io;
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