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
#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

inline bool CharIsA(const char &c) {
  return c == 'a' || c == 'A';
}

std::vector<std::string> ContainsA(const std::string &s) {
  std::vector<std::string> words_with_a{};
  // Whitespace/Non-whitespace flags
  bool has_a{false};
  bool cur_char_is_space{false};

  // Word begin & end pointers
  auto word_begin{s.begin()};
  auto word_end{s.begin()};

  // Conditions for checking word boundaries
  auto word_is_ending{[&cur_char_is_space](auto it) {
    return isspace(*it) && !cur_char_is_space;
  }};
  auto is_in_middle_of_word{
    [&cur_char_is_space]() { return !cur_char_is_space; }};
  auto word_is_starting{[](const char &c) { return !isspace(c); }};

  // Main loop
  for (auto it{s.begin()}, e{s.end()}; it != e; ++it) {
    if (word_is_ending(it)) {
      cur_char_is_space = true;
      word_end = it;
      if (has_a) {
        words_with_a.emplace_back(std::string(word_begin, word_end));
      }
    } else if (is_in_middle_of_word()) {
      has_a = has_a || CharIsA(*it);
    } else if (word_is_starting(*it)) {
      cur_char_is_space = false;
      word_begin = it;
      has_a = CharIsA(*it);
    }
  }
  // Maybe emplace final word of string.
  if (!cur_char_is_space && has_a)
    words_with_a.emplace_back(std::string(word_begin, s.end()));
  return words_with_a;
}

TEST_CASE ("test ContainsA") {
    CHECK_EQ(ContainsA("This text contains 3 words with an 'A'"),
             (std::vector<std::string>{"contains", "an", "'A'"}));
    CHECK(ContainsA("").empty());
    CHECK_EQ(ContainsA("aaaaaaaaaaaaaaaaaaaaaa"),
             std::vector<std::string>{"aaaaaaaaaaaaaaaaaaaaaa"});
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
  std::string user_input{};
  io << "Introduzca un texto: ";
  if (!io.GetInputFromUser()) return 0;
  io.GetLine(user_input);
  io << "Estas palabras contienen 'a' o 'A': ";
  std::vector result{ContainsA(user_input)};
  io << CollectionString(result.begin(), result.end()) << '\n';
  return res;
}