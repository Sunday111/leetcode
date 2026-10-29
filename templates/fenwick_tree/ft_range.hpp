#pragma once

#include <concepts>
#include <type_traits>

#include "ft_prefix.hpp"

// Returns the aggregate over [begin, end).
template <typename T, std::unsigned_integral Index, typename Traits>
[[nodiscard, gnu::always_inline]] constexpr T ft_range(
    const FenwickTree<T, Index, Traits>& tree,
    std::type_identity_t<Index> begin,
    std::type_identity_t<Index> end) noexcept
{
    using Inv = typename Traits::Inv;
    return static_cast<T>(Inv{}(ft_prefix(tree, end), ft_prefix(tree, begin)));
}
