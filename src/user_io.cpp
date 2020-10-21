#include <stdexcept>
#include "user_io.h"

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
