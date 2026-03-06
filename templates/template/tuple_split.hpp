#pragma once

#include <tuple>

#include "concept/is_specialization.hpp"

template <std::size_t k, is_specialization<std::tuple> T>
[[nodiscard]] constexpr auto tuple_split(T&& x) noexcept
{
    constexpr auto n = std::tuple_size_v<T>;
    static_assert(k <= n);

    return std::make_tuple(
        [&]<std::size_t... indices>(std::index_sequence<indices...>)
        {
            return std::make_tuple(std::get<indices>(std::forward<T>(x))...);
        }(std::make_index_sequence<k>()),
        [&]<std::size_t... indices>(std::index_sequence<indices...>)
        {
            return std::make_tuple(
                std::get<k + indices>(std::forward<T>(x))...);
        }(std::make_index_sequence<n - k>()));
}
