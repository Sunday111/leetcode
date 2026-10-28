#pragma once

#include <concepts>
#include <cstddef>

#include "st.hpp"

// Source and buffer must not overlap; buffer must hold
// st_required_buffer_size(n) elements.
template <typename T, std::unsigned_integral Index, typename Op>
[[nodiscard, gnu::always_inline]] constexpr SparseTable<T, Index, Op>
st_make(const T* source, Index n, T* buffer) noexcept
{
    for (Index i = 0; i != n; ++i)
    {
        buffer[i] = source[i];
    }

    const std::size_t size = n;
    T* previous = buffer;
    for (std::size_t half = 1; half <= size / 2; half *= 2)
    {
        T* current = previous + size;
        const auto count = static_cast<Index>(size - 2 * half + 1);
        for (Index i = 0; i != count; ++i)
        {
            current[i] = static_cast<T>(Op{}(previous[i], previous[i + half]));
        }
        previous = current;
    }

    return {buffer, n};
}
