#pragma once

#include <concepts>
#include <type_traits>

#include "ft_at.hpp"

template <typename T, std::unsigned_integral Index, typename Traits>
[[gnu::always_inline]] constexpr void ft_update(
    const FenwickTree<T, Index, Traits>& tree,
    std::type_identity_t<Index> index,
    std::type_identity_t<T> value) noexcept
{
    using Op = typename Traits::Op;
    using Inv = typename Traits::Inv;
    T previous = ft_at(tree, index);
    for (Index i = index; i < tree.size; i = static_cast<Index>(i | (i + 1)))
    {
        tree.x[i] = static_cast<T>(Op{}(Inv{}(tree.x[i], previous), value));
    }
}
