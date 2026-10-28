#pragma once

#include <concepts>
#include <type_traits>

#include "ft_range.hpp"

template <typename T, std::unsigned_integral Index, typename Traits>
[[nodiscard, gnu::always_inline]] constexpr T ft_at(
    const FenwickTree<T, Index, Traits>& tree,
    std::type_identity_t<Index> index) noexcept
{
    return ft_range(tree, index, static_cast<Index>(index + 1));
}
