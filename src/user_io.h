//
// Created by callisto on 10/12/20.
//

#pragma once

#include <ostream>
#include <iostream>
#include <optional>
#include <sstream>

class UserIO {
 public:
  UserIO();
  ~UserIO();

  template<typename T>
  inline void Err(T what) {
    errstream << what;
  }

  operator bool();

  template<typename T>
  UserIO& operator<<(T s) {
    Tell(s);
    return *this;
  }

  template<typename T>
  inline void Tell(T data) {
    ostream << data;
  };

  template<typename T>
  inline bool Token(T &token) {
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

  bool Eof();

  bool Fail();

 private:
  template<typename T>
  void FailParseMessage() {
    errstream << "No pude interpretar el input como una variable de tipo "
              << var_name<T> << ".\nIntenta de nuevo.\n";
  };

  std::ostream &ostream;
  std::istream &istream;
  std::stringstream buffer{};
  std::ostream &errstream;
  template<typename T>
  static constexpr char* var_name{};
  template<> static constexpr const char* var_name<double>{"double"};
  template<> static constexpr const char* var_name<int>{"int"};
  template<> static constexpr const char* var_name<std::string>{"palabra"};
  template<> static constexpr const char* var_name<bool>{"bool"};
};

struct Interactions {
    const char *const hello;
    const char *const bye;
    const char *const fail;
    const char *const try_again;
};
