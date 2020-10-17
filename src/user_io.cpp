#include <cmath>
#include <stdexcept>
#include "user_io.h"

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
      throw std::runtime_error("No puedo interpretar un decimal como entero");
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
    buffer.str(s);
    buffer.clear(); // Reset flags
  }
  return ok;
}

UserIO::operator bool() {
  return bool(buffer);
}
