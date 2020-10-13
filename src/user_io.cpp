//
// Created by callisto on 10/12/20.
//

#include "user_io.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

UserIO::UserIO() : istream{std::cin}, ostream{std::cout},
                   errstream{std::cerr} {
  Tell("Bienvenido!\n");
  Tell("Para cerrar presiona Ctrl-c o Ctrl-d.\n");
}

template<>
bool UserIO::Token(int &token) {
  double numd;
  if (buffer >> numd) {
    if (numd > std::numeric_limits<int>::max() ||
        numd < std::numeric_limits<int>::min()) {
      throw std::overflow_error("Int overflow");
    }
    double int_part_d;
    double fract_part_d{std::modf(numd, &int_part_d)};
    if (fract_part_d != 0)
      throw std::runtime_error("Can't parse int from fractional");
    token = static_cast<int>(int_part_d);
    return true;
  } else {
    FailParseMessage<int>();
    return false;
  }
}

bool UserIO::GetLine(std::string &token) {
  std::string s{buffer.str()};
  if (s.empty()) {
    return false;
  } else {
    token = s;
    return true;
  }
}

[[nodiscard]] bool UserIO::GetInputFromUser() {
  std::string s{};
  bool ok{std::getline(istream, s)};
  if (ok) {
    buffer = std::move(std::stringstream{s});
  }
  return ok;
}

bool UserIO::Eof() {
  return buffer.eof();
}

bool UserIO::Fail() {
  return buffer.fail();
}

UserIO::operator bool() {
  return bool(buffer);
}

UserIO::~UserIO() {
  Tell("Bye!\n");
}
