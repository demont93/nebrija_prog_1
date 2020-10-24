//===-- ejercicio38.cpp -----------------------------------------*- C++ -*-===//
///
/// \file
/// Ejercicio38
/// ===========
/// Programa que solucione una ecuación de 2º grado a·X2+b·X+c=0, pidiendo al
/// usuario los valores de a, b y c.
///
//===----------------------------------------------------------------------===//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "user_io.h"
#include <complex>
#include <cassert>

std::pair<std::complex<double>, std::complex<double>>
QuadFun(double a, double b, double c) {
  assert(a != 0 && "Not quadratic");
  double divisor{2 * a};
  double radicand{(b * b) - (4 * a * c)};
  if (radicand < 0) {
    double root{std::sqrt(radicand * -1)};
    double x_1 = ((b * (-1)) / divisor);
    return {{x_1, root},
            {x_1, -1 * root}};
  } else {
    double root{std::sqrt(radicand)};
    double x_1 = ((b * (-1)) + root) / divisor;
    double x_2 = ((b * (-1)) - root) / divisor;
    return {{x_1},
            {x_2}};
  }
}

std::string FormatComplex(std::complex<double> &complex) {
  std::stringstream ss{};
  ss << complex.real();
  if (complex.imag() > 0)
    ss << " + " << complex.imag() << 'i';
  else if (complex.imag() < 0)
    ss << " - " << complex.imag() * -1 << 'i';
  return ss.str();
}

TEST_CASE ("Test roots") {
    CHECK_EQ(QuadFun(1, -2, 1),
             std::pair{std::complex{1.0}, std::complex{1.0}});
    CHECK_EQ(QuadFun(1, 7, 12),
             std::pair{std::complex{-3.0}, std::complex{-4.0}});
  auto res = QuadFun(1, 1, 1);
    CHECK_EQ(res.first.real(), -0.5);
    CHECK_EQ(res.second.real(), -0.5);
    CHECK_EQ(res.first.imag(), doctest::Approx(1.73205).epsilon(0.00001));
    CHECK_EQ(res.second.imag(), doctest::Approx(-1.73205).epsilon(0.00001));
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
  io << "Calculemos las raices de una funcion cuadratica.\n";
  while (true) {
    try {
      int a, b, c;
      bool success{
        io.Ask("Introduce a: ", a) &&
        io.Ask("Introduce b: ", b) &&
        io.Ask("Introduce c: ", c)
      };
      if (!success) return res;
      if (a == 0)
        throw std::runtime_error("Si a == 0, la funcion no es cuadratica.");
      io << "Las raices son:\n";
      auto result{QuadFun(a, b, c)};
      io << "x1 = " << FormatComplex(result.first) << '\n';
      io << "x2 = " << FormatComplex(result.second) << '\n';
      return res;
    } catch (std::runtime_error &e) {
      io.Err(e.what());
      io.Err('\n');
    }
  }
}