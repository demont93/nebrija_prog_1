#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>

template<typename Iterator>
void PrintCollection(Iterator begin, Iterator end) {
  std::cout << '[';
  if (begin != end) {
    std::cout << *begin;
    while (++begin != end) {
      std::cout << ", " << *begin;
    }
  }
  std::cout << ']';
}

template<typename Iterator>
std::string CollectionString(Iterator begin, Iterator end) {
  std::stringstream out{};
  out << '[';
  if (begin != end) {
    out << *begin;
    while (++begin != end) {
      out << ", " << *begin;
    }
  }
  out << ']';
  return out.str();
}

template<typename T>
void FillRandomInts(T begin, T end, int from, int to) {
  auto seed{
    static_cast<unsigned int>(std::chrono::high_resolution_clock::now()
      .time_since_epoch()
      .count())};
  std::default_random_engine gen(seed);
  std::uniform_int_distribution<int> distribution(from, to);
  while (begin != end) {
    *begin = distribution(gen);
    ++begin;
  }
};

