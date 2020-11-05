//===-- ejercicio40.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio40
/// ===========
/// Pedir al usuario día, mes y año de nacimiento. Devolver signo de zodiaco y
/// edad actual.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "user_io.h"
#include <ctime>
#include <array>
#include <cassert>

struct Date {
  // Date(int day, int month, int year) : day{day}, month{month}, year{year} {}

  [[nodiscard]] Date WithYear(int ryear) const {
    return Date{day, month, ryear};
  }

  bool operator==(const Date &rhs) const {
    return day == rhs.day && year == rhs.year && month == rhs.month;
  }

  bool operator<(const Date &rhs) const {
    return year < rhs.year ||
           (year == rhs.year &&
            (month < rhs.month || (month == rhs.month && day < rhs.day)));
  }

  bool operator>(const Date &rhs) const {
    return rhs < *this;
  }

  [[nodiscard]] int YearDiff(const Date &rhs) const {
    int result;
    if (*this < rhs) {
      result = rhs.year - year;
      if (rhs.LessMonthAndDay(*this)) --result;
    } else if (rhs < *this) {
      result = year - rhs.year;
      if (LessMonthAndDay(rhs)) --result;
    } else {
      result = 0;
    }
    return result;
  }

  [[nodiscard]] bool LessMonthAndDay(const Date &rhs) const {
    return month < rhs.month || (month == rhs.month && day < rhs.day);
  };

  [[nodiscard]] bool LessEqMonthAndDay(const Date &rhs) const {
    return month < rhs.month || (month == rhs.month && day <= rhs.day);
  }

  static constexpr int month_max_days[12]{31, 29, 31, 30, 31, 30, 31, 31, 30,
                                          31, 30, 31};
  const int day;
  const int month;
  const int year;
};

bool IsLeapYear(int year) {
  return year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0);
}

bool ValidateDate(const Date &date) {
  if (date.year < 0 || date.month < 0 || date.day < 0) return false;
  if (date.month == 2 && date.day == 29 && !IsLeapYear(date.year)) return false;
  if (date.day > Date::month_max_days[date.month - 1]) return false;
  if (date.month > 12) return false;
  return true;
}

int Age(const Date &time_before) {
  time_t now;
  std::time(&now);
  auto nowtm{std::localtime(&now)};
  Date now_date{nowtm->tm_mday, nowtm->tm_mon + 1, nowtm->tm_year + 1900};
  std::cout << now_date.day << " " << now_date.month << " " << now_date.year
            << '\n';
  if (now_date < time_before)
    throw std::runtime_error("Esta fecha es en el futuro");
  return now_date.YearDiff(time_before);
}

std::string Starcult(Date &date) {
  static std::array<Date, 13> star_cult_tags{{{19, 1, 0}, {18, 2, 0},
                                               {20, 3, 0}, {20, 4, 0},
                                               {20, 5, 0}, {20, 6, 0},
                                               {20, 7, 0}, {21, 8, 0},
                                               {22, 9, 0}, {22, 10, 0},
                                               {22, 11, 0}, {31, 12, 0}}};
  static const char *names[13]{"Capricornio", "Acuario", "Piscis", "Aries",
                               "Tauro", "Geminis", "Cancer", "Leo", "Virgo",
                               "Libra", "Escoropio", "Sagitario",
                               "Capricornio"};
  Date date_no_year{date.WithYear(0)};
  for (int i{0}; i < 13; ++i) {
    if (date_no_year.LessEqMonthAndDay(star_cult_tags[i])) return names[i];
  }
  assert(false && "shouldn't reach here, no zodiac selected");
}

TEST_CASE ("") {
  Date date = Date{3, 12, 10};
    CHECK_EQ(date.YearDiff(Date{3, 12, 10}), 0);
    CHECK_EQ(date.YearDiff(Date{3, 12, 11}), 1);
    CHECK_EQ(date.YearDiff(Date{4, 12, 11}), 1);
    CHECK_EQ(date.YearDiff(Date{2, 12, 11}), 0);
  Date date_2 = Date{7, 9, 1993};
    CHECK_EQ(date_2.YearDiff(Date{5, 11, 2020}), 27);
}

TEST_CASE ("zodiac") {
  Date date{7, 9, 1993};
    CHECK_EQ(Starcult(date), "Virgo");
  Date date_2{22, 10, 1928};
    CHECK_EQ(Starcult(date_2), "Libra");
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
      io
        << "Introduce tu fechar de nacimiento en forma de dia mes y año separado "
        << "por espacios.\nEjemplo: 31 12 1963\n";
      if (!io.GetInputFromUser()) return res;
      int year, month, day;
      io.Token(day);
      io.Token(month);
      io.Token(year);
      Date user_date{day, month, year};
      if (!ValidateDate(user_date)) {
        io.Err("Fecha no valida\n");
        continue;
      }
      auto age{Age(user_date)};
      auto zodiac{Starcult(user_date)};
      io << "Tu edad es " << age << " año(s) y tu signo zodiacal es "
         << zodiac << '\n';
      return res;
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
      continue;
    }
  }
}