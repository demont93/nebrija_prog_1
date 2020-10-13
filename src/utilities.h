#include <vector>
#include <iostream>
#include <sstream>

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