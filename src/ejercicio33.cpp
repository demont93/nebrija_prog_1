//===-- ejerjcicio33.cpp ----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio33
/// ===========
/// Introducir un texto por consola y devolver todas las palabras que tengan mas
/// de 3 vocales.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "utilities.h"
#include "user_io.h"

template<typename T>
void Words3Vowels(std::string s, T &output) {
  Tokenizer tok{s};
  for (auto &word : tok) {
    size_t vowel_position{word.find_first_of("aeiouAEIOU")};
    for (int t{0}; t < 2 && vowel_position != std::string::npos; ++t)
      vowel_position = word.find_first_of("aeiouAEIOU", vowel_position + 1);
    if (vowel_position != std::string::npos)
      output << word << ' ';
  }
  output << '\n';
}


TEST_CASE ("test") {
  std::stringstream ss{};

  ss.str("");
  Words3Vowels("hellou what is itAAAA that is upuU", ss);
    CHECK_EQ(ss.str(), "hellou itAAAA upuU \n");

  ss.str("");
  Words3Vowels("holaaaaaa aaaaaaaaaaaaa aaaaaaaaaaaa", ss);
    CHECK_EQ(ss.str(), "holaaaaaa aaaaaaaaaaaaa aaaaaaaaaaaa \n");
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
  io << "Introduce una oracion.\n";
  if (!io.GetInputFromUser()) return res;
  std::string user_input;
  io.GetLine(user_input);
  io << "Palabras con 3 vocales: ";
  Words3Vowels(user_input, io);

  return res;
}