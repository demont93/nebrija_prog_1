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

  template<>
  bool Token(int &token);

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
