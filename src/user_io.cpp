#include <stdexcept>
#include "user_io.h"

bool UserIo::GetLine(std::string &token) {
  std::string s{buffer.str()};
  if (s.empty()) {
    return false;
  } else {
    token = s;
    return true;
  }
}

[[nodiscard]] bool UserIo::GetInputFromUser() {
  std::string s{};
  bool ok{static_cast<bool>(std::getline(istream, s))};
  if (ok) {
    buffer.str(s);
    buffer.clear(); // Reset flags
  }
  return ok;
}

UserIo::operator bool() {
  return bool(buffer);
}
