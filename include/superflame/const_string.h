#pragma once
#ifndef CONST_STRING_H_
#define CONST_STRING_H_
#include "traits.h"
#include <cstdint>

namespace superflame {

template<std::size_t SIZE>
struct constexpr_str {
    char const * str;
    static constexpr std::size_t size = SIZE - 1;
    template <std::size_t N, typename enable_if<(SIZE == N), bool>::type = true>
    constexpr explicit constexpr_str(char const (&s)[N])
    :str(s) {}
};

template<std::size_t N>
constexpr auto make_constexpr_str(char const (&s)[N]) -> constexpr_str<N> {
    return constexpr_str<N> {s};
}
}  // namespace superflame

#define CXX_MAKE_TYPED_LITERNAL(NAME, LITERAL) decltype(superflame::make_constexpr_str(LITERAL)) NAME {LITERAL};



#endif  // CONST_STRING_H_
