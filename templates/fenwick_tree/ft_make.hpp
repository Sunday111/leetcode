#pragma once

#include <concepts>

#include "ft.hpp"

// Source and buffer must not overlap; buffer must hold n elements.
template <typename T, std::unsigned_integral Index, typename Traits>
[[nodiscard, gnu::always_inline]] constexpr FenwickTree<T, Index, Traits>
ft_make(const T* source, Index n, T* buffer) noexcept
{
    using Op = typename Traits::Op;
    for (Index i = 0; i != n; ++i)
    {
        buffer[i] = source[i];
    }

    for (Index i = 0; i != n; ++i)
    {
        const Index parent = static_cast<Index>(i | (i + 1));
        if (parent < n)
        {
            buffer[parent] = static_cast<T>(Op{}(buffer[parent], buffer[i]));
        }
    }

    return {buffer, n};
}
