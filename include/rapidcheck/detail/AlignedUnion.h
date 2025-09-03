#pragma once
#include <cstddef>

namespace rc {
namespace detail {

template <std::size_t... Vs>
struct MaxOf;

template <std::size_t V>
struct MaxOf<V> : public std::integral_constant<std::size_t, V> {};

template <std::size_t V1, std::size_t V2, std::size_t... Vs>
struct MaxOf<V1, V2, Vs...>
    : public std::integral_constant<
          std::size_t,
          (V1 > MaxOf<V2, Vs...>::value ? V1 : MaxOf<V2, Vs...>::value)> {};

/// Replacement for std::aligned_union for compiles that do not have it.
template <typename... Ts>
class AlignedUnion {
private:
  alignas(Ts...) std::byte t_buff[std::max({sizeof(Ts)...})];
};
} // namespace detail
} // namespace rc
