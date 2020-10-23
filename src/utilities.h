#include <vector>
#include <optional>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>

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
}

template<typename U=std::string::iterator, typename T=int (*)(int)>
class Tokenizer {
 public:
  Tokenizer() = delete;
  explicit Tokenizer(std::string &s);

  class Iterator;

  Iterator begin();
  Iterator end();
 private:
  T delimiter_f;
  U s_begin;
  U s_end;
};

template<typename U, typename T>
Tokenizer<U, T>::Tokenizer(std::string &s) : s_begin{s.begin()},
                                             s_end{s.end()},
                                             delimiter_f{isspace} {}

template<typename U, typename T>
class Tokenizer<U, T>::Iterator {
 public:
  Iterator() = delete;
  explicit Iterator(U s_begin, U s_end, T f);
  Iterator &operator++();
  std::string &operator*();
  bool operator==(const Iterator &iter) const;
 private:
  void SkipWs();
  void SkipNoWs();
  U s_begin;
  U s_end;
  T f;
  std::string buf;
  bool valid;
};

template<typename U, typename T>
Tokenizer<U, T>::Iterator::Iterator(U s_begin, U s_end, T f)
  : s_begin{s_begin},
    s_end{s_end},
    f{f},
    buf{},
    valid{s_begin != s_end} {
  this->operator++();
}

template<typename U, typename T>
typename Tokenizer<U, T>::Iterator &Tokenizer<U, T>::Iterator::operator++() {
  if (s_begin != s_end) {
    buf.clear();
    SkipWs();
    auto from{s_begin};
    SkipNoWs();
    std::copy(from, s_begin, std::back_inserter(buf));
    return *this;
  } else {
    valid = false;
    return *this;
  }
}

template<typename U, typename T>
std::string &Tokenizer<U, T>::Iterator::operator*() {
  return buf;
}

template<typename U, typename T>
bool Tokenizer<U, T>::Iterator::operator==(const Iterator &iter) const {
  return (valid && iter.valid) ?
         (s_begin == iter.s_begin && s_end == iter.s_end) :
         (valid == iter.valid);
}

template<typename U, typename T>
void Tokenizer<U, T>::Iterator::SkipWs() {
  while (s_begin != s_end && f(*s_begin)) ++s_begin;
}

template<typename U, typename T>
void Tokenizer<U, T>::Iterator::SkipNoWs() {
  while (s_begin != s_end && !f(*s_begin)) ++s_begin;
}

template<typename U, typename T>
typename Tokenizer<U, T>::Iterator Tokenizer<U, T>::begin() {
  return Iterator(s_begin, s_end, delimiter_f);
}

template<typename U, typename T>
typename Tokenizer<U, T>::Iterator Tokenizer<U, T>::end() {
  return Iterator(s_end, s_end, delimiter_f);
}
