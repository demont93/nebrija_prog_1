#pragma once

#include <ostream>
#include <iostream>
#include <optional>
#include <sstream>

class UserIO {
 public:
  UserIO() = default;

  template<typename T>
  inline void Err(T what) {
    errstream << what;
  }

  explicit operator bool();

  template<typename T>
  UserIO &operator<<(T s) {
    Tell(s);
    return *this;
  }

  template<typename T>
  void Tell(T data) {
    ostream << data;
  };

  template<typename T>
  bool Token(T &token) {
    if (buffer >> token) {
      return true;
    } else {
      FailParseMessage<T>();
      return false;
    }
  }

  template <> inline bool UserIO::Token(int &token) {
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

  bool GetLine(std::string &token);

  [[nodiscard]] bool GetInputFromUser();

 private:
  template<typename T>
  void FailParseMessage() {
    throw std::runtime_error(
      std::string{"No pude interpretar el input como una variable de tipo "} +
      var_name < T > +".\nIntenta de nuevo.\n");
  };

  std::ostream &ostream{std::cout};
  std::istream &istream{std::cin};
  std::stringstream buffer{};
  std::ostream &errstream{std::cerr};
  template<typename>
  static constexpr char *var_name{};
  template<> static constexpr const char *var_name<double>{"double"};
  template<> static constexpr const char *var_name<int>{"int"};
  template<> static constexpr const char *var_name<std::string>{"palabra"};
  template<> static constexpr const char *var_name<bool>{"bool"};
};
