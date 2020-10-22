//===-- ejercicio13.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio13
/// Pedir al usuario que introduzca un texto por teclado y mostrar todas las
/// palabras que contengan al menos una "a".
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <array>
#include <vector>
#include <string_view>
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

inline bool CharIsA(const char &c) {
  return c == 'a' || c == 'A';
}

template<typename T>
void SkipWs(T &begin, T end) {
  while (isspace(*begin) && begin != end)
    ++begin;
}

template<typename T>
inline bool WordWithA(T begin, T &end) {
  begin = std::find_if(begin, end, [](const char &c) {
    return CharIsA(c) || isspace(c);
  });
  if (CharIsA(*begin)) {
    end = std::find_if(begin, end, isspace);
    return true;
  } else {
    end = begin;
    return false;
  }
}

template<typename T>
void ContainsA(const std::string &s, T &out) {
  auto w_end{s.begin()};
  auto it{s.begin()};
  auto e{s.end()};
  while (it != e) {
    SkipWs(it, e);
    if (WordWithA(it, (w_end = e))) {
      for (; it != w_end; ++it) out << *it;
      out << ' ';
      it = w_end;
    }
    it = w_end;
  }
}

TEST_CASE ("test ContainsA") {
  std::stringstream ss{};
    REQUIRE_EQ(ss.str(), "");

    SUBCASE("one") {
    ContainsA("hola", ss);
      CHECK_EQ(ss.str(), "hola ");
  }
    SUBCASE("many") {
    ContainsA("hola como estas", ss);
      CHECK_EQ(ss.str(), "hola estas ");
  }
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
  std::string user_input{};
  io << "Introduzca un texto: ";
  if (!io.GetInputFromUser()) return 0;
  io.GetLine(user_input);
  io << "Estas palabras contienen 'a' o 'A': ";
  ContainsA(user_input, io);
  return res;
}