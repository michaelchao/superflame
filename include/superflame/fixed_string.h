#ifndef FIXED_STRING_H_
#define FIXED_STRING_H_
#include "const_string.h"
#include <cstring>
#include <string>

namespace superflame {
template<size_t N>
class fixed_string {
public:
  fixed_string() {}

  template<size_t M, CONCEPT_REQUIRE(M <= N)>
  void assign(char const (&s)[M]) {
    std::memcpy(data_, s, M - 1);
    data_[M] = 0;
    data_size_ = M - 1;
  }

  void assign(char const * s, size_t size) {
    std::memcpy(data_, s, size);
    data_size_ = size;
  }

  const char * c_str() const noexcept {
    return data_;
  }

  constexpr size_t size() const noexcept {
    return data_size_;
  }

  char & operator [](int index) {
    return data_[index];
  }

  fixed_string<N> & push_back(char c) {
    data_[data_size_] = c;
    data_size_ += 1;
    return *this;
  }

  template<size_t M>
  fixed_string<N> & push_back(const fixed_string<M> & str) {
    memcpy(data_ + data_size_, str.c_str(), str.size());
    data_size_ = data_size_ + str.size();
    data_[data_size_] = 0;
    return *this;
  }

  template<size_t M, CONCEPT_REQUIRE(M <= N)>
  fixed_string<N> & push_back(char const (&s)[M]) {
    memcpy(data_ + data_size_, s, M - 1);
    data_size_ = data_size_ + M - 1;
    data_[data_size_] = 0;
    return *this;
  }

  template<size_t SIZE>
  fixed_string<N> & push_back(const constexpr_str<SIZE> & cs) {
    memcpy(data_ + data_size_, cs.str, cs.size);
    data_size_ = data_size_ + cs.size;
    data_[data_size_] = 0;
    return *this;
  }

  template<size_t N1>
  fixed_string<N + N1> operator +(const fixed_string<N1> & other) {
    fixed_string<N + N1> temp;
    temp.push_back(*this);
    temp.push_back(other);
    return temp;
  }

private:
  char data_[N] {0};
  size_t data_size_ {0U};
};

template<size_t SIZE>
fixed_string<SIZE> fixed_string_from(char const (&s)[SIZE]) {
  fixed_string<SIZE> str;
  str.assign(s);
  return str;
}

template<size_t SIZE>
fixed_string<SIZE> fixed_string_from(const constexpr_str<SIZE> & cs) {
  fixed_string<SIZE> str;
  str.assign(cs.str, cs.size);
  return str;
}

template<size_t SIZE>
std::string to_std_string(const fixed_string<SIZE> & str) {
  std::string out;
  out.reserve(SIZE);
  out.assign(str.c_str(), str.size());
  return out;
}

} // namespace superflame

#endif // FIXED_STRING_H_