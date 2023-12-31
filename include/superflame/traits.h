#pragma once
#ifndef TRAITS_H_
#define TRAITS_H_

#include <cstddef>
#include <type_traits>

namespace superflame {

template<bool _Test, typename _Ty>
struct enable_if {
};

template<class _Ty>
struct enable_if<true, _Ty> { typedef _Ty type; };

template<bool _Test, class _Ty = void>
using enable_if_t = typename enable_if<_Test, _Ty>::type;

template <typename T>
struct is_function_pointer : std::false_type {};

template <typename ReturnType, typename... ArgTypes>
struct is_function_pointer<ReturnType (*)(ArgTypes...)> : std::true_type {};


} // namespace superflame

#define CONCEPT_REQUIRE(cond) \
  typename superflame::enable_if<(cond), bool>::type = true

#endif // TRAITS_H_