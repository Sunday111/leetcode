#pragma once

#include <concepts>
#include <type_traits>

#include "ft.hpp"

// Returns the aggregate over [0, end).
template <typename T, std::unsigned_integral Index, typename Traits>
[[nodiscard, gnu::always_inline]] constexpr T ft_prefix(
    const FenwickTree<T, Index, Traits>& tree,
    std::type_identity_t<Index> end) noexcept
{
    using Op = typename Traits::Op;
    T result{Traits::identity};
    while (end)
    {
        result = static_cast<T>(Op{}(result, tree.x[end - 1]));
        end = static_cast<Index>(end & (end - 1));
    }
    return result;
}
