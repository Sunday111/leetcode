#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <type_traits>

#include "integral_aliases.hpp"
#include "radix_sort_indices_by.hpp"

template <
    u32 key_bits,
    u32 capacity = 100'001,
    std::unsigned_integral I,
    typename Proj>
[[gnu::no_sanitize_address, gnu::flatten]] void
adaptive_sort_indices_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(key_bits > 0 && key_bits <= sizeof(Key) * 8);
    assert(n <= capacity);  // NOLINT

    if (n < 256)
    {
        std::ranges::sort(indices, indices + n, std::less{}, proj);
    }
    else if (n < 1280)
    {
        radix_sort_indices_by<
            std::min(8u, key_bits),
            (key_bits + 7) / 8,
            std::min(capacity, 1279u)>(indices, n, proj);
    }
    else if (n < 8192)
    {
        radix_sort_indices_by<
            std::min(10u, key_bits),
            (key_bits + 9) / 10,
            std::min(capacity, 8191u)>(indices, n, proj);
    }
    else
    {
        radix_sort_indices_by<
            std::min(13u, key_bits),
            (key_bits + 12) / 13,
            capacity>(indices, n, proj);
    }
}
