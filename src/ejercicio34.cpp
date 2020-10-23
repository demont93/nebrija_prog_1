//===-- ejercicio34.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio34
/// ===========
/// Programa que calcule la letra del DNI [Información Letra
/// DNI](http://www.interior.gob.es/web/servicios-al-ciudadano/dni/calculo-del-digito-de-control-del-nif-nie\)
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include "doctest.h"
#include "user_io.h"

template<typename T>
[[nodiscard]] std::optional<int> ParseNat(T begin, T end) noexcept {
  if (begin == end) return {};
  int result{0};

  for (; begin != end; ++begin) {
    const char &c{*begin};
    if (c < '0' || c > '9') return {};
    if (result > std::numeric_limits<int>::max() / 10) return {};
    int digit = c - '0';
    (result *= 10) += digit;
  }
  return {result};
}

[[nodiscard]] constexpr int DniMod(const int num_dni) noexcept {
  assert(num_dni > 0 && num_dni <= 99999999);
  return num_dni % 23;
}

[[nodiscard]] constexpr char DniCharFromMod(const int mod) noexcept {
  assert(mod >= 0 && mod <= 22);
  constexpr std::array<char, 23> lookup_table{'T', 'R', 'W', 'A', 'G', 'M', 'Y',
                                              'F', 'P', 'D', 'X', 'B', 'N', 'J',
                                              'Z', 'S', 'Q', 'V', 'H', 'L', 'C',
                                              'K', 'E'};
  return lookup_table[mod];
}

[[nodiscard]] constexpr char DniEsp(const int num_dni) noexcept {
  assert(num_dni > 0 && num_dni <= 99999999);
  return DniCharFromMod(DniMod(num_dni));
}

[[nodiscard]] constexpr int Normalize(const std::string &dni_string) {
  if (dni_string.size() != 8)
    throw std::runtime_error("Longitud de dni debe ser 8.");
  int first_digit;
  if (isdigit(dni_string[0])) {
    first_digit = static_cast<int>(dni_string[0] - '0');
  } else {
    switch (dni_string[0]) {
      case 'X':
        first_digit = 0;
        break;
      case 'Y':
        first_digit = 1;
        break;
      case 'Z':
        first_digit = 2;
        break;
      default:
        throw std::runtime_error{"Primer caracter no es digito ni X,Y,Z"};
    }
  }
  auto result{ParseNat(dni_string.begin() + 1, dni_string.end())};
  if (result) return *result + first_digit * static_cast<int>(std::pow(10, 7));
  else throw std::runtime_error("dni malformado.");
}

[[nodiscard]] constexpr char
CalculateSpecialChar(const std::string &dni_string) {
  int dni_num{Normalize(dni_string)};
  return DniEsp(dni_num);
}

TEST_CASE ("Num Dni Mod") {
    CHECK_EQ(DniMod(12345678), 14);
}

TEST_CASE ("Letra a partir de mod") {
    CHECK_EQ(DniCharFromMod(14), 'Z');
}

TEST_CASE ("NIF espanoles residentes") {
    CHECK_EQ(DniEsp(12345678), 'Z');
}

TEST_CASE ("Convertir a Dni normal") {
    CHECK_EQ(Normalize("12345678"), 12345678);
    CHECK_EQ(Normalize("Z2345678"), 22345678);
    CHECK_THROWS(Normalize(""));
    CHECK_THROWS(Normalize("1234567"));
    CHECK_THROWS(Normalize("z2345678"));
    CHECK_THROWS(Normalize(""));
}

TEST_CASE ("ParseNat") {
  std::string nat{"12345"};
  std::string overflow_nat{"9238472937492347234"};
    CHECK_EQ(*ParseNat(nat.begin(), nat.end()), 12345);
    CHECK_EQ(*ParseNat(nat.begin(), nat.end() - 2), 123);
    CHECK_EQ(ParseNat(overflow_nat.begin(), overflow_nat.end()), std::nullopt);
    CHECK_EQ(ParseNat(nat.end(), nat.end()), std::nullopt);
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
  while (true) {
    try {
      io << "Introduce un numero de dni sin el "
         << "caracter especial para calcularlo: ";
      if (!io.GetInputFromUser()) return res;
      std::string user_input;
      io.GetLine(user_input);
      io << CalculateSpecialChar(user_input);
      return res;
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}