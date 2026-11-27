#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <limits>
#include <type_traits>

#include "radix_sort/radix_sort.hpp"

// max_key bounds the selected field after shifting. Ties may be reordered.
template <
    u32 key_bits,
    u32 capacity = 100'001,
    u32 skip_bits = 0,
    std::unsigned_integral T>
    requires(
        sizeof(T) > 1 && key_bits > 0 &&
        u64{skip_bits} + key_bits <= sizeof(T) * 8)
[[gnu::always_inline]] inline void adaptive_sort(
    T* data,
    u32 n,
    std::type_identity_t<T> max_key = std::numeric_limits<T>::max()) noexcept
{
    assert(n <= capacity);  // NOLINT
    if (n < 2) return;
    if (n < 64)
    {
        if constexpr (skip_bits + key_bits == sizeof(T) * 8)
        {
            std::sort(data, data + n);
        }
        else
        {
            constexpr T mask = (T{1} << key_bits) - 1;
            std::ranges::sort(
                data,
                data + n,
                std::less{},
                [](T v) { return (v >> skip_bits) & mask; });
        }
        return;
    }

    if constexpr (key_bits > 8)
    {
        if (max_key < 256)
        {
            radix_sort<8, 8, SortOrder::Ascending, capacity, skip_bits>(
                data,
                n);
            return;
        }
    }
    if constexpr (key_bits > 16)
    {
        if (max_key < 65'536)
        {
            radix_sort<16, 8, SortOrder::Ascending, capacity, skip_bits>(
                data,
                n);
            return;
        }
    }
    radix_sort<key_bits, 8, SortOrder::Ascending, capacity, skip_bits>(data, n);
}
