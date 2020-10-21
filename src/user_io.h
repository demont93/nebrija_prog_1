//===-- user_io.h -----------------------------------------------*- C++ -*-===//
///
/// \file
/// Punto de entrada para todas las funciones de I/O tipicas de los "toy
/// exercises".
///
//===----------------------------------------------------------------------===//

#pragma once

#include <ostream>
#include <iostream>
#include <optional>
#include <sstream>
#include <cmath>

class UserIo {
 public:
  UserIo() = default;

  /// Envia un mensaje de error al usuario.
  template<typename T>
  inline void Err(T what) {
    errstream << what;
  }

  template<typename T>
  UserIo &operator<<(T s) {
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

  template<>
  inline bool Token(int &token) {
    double numd{0};
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
      var_name<T> +".\nIntenta de nuevo.\n");
  };

  explicit operator bool();

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
