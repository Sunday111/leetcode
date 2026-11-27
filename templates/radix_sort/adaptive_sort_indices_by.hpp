#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <type_traits>

#include "integral_aliases.hpp"
#include "radix_sort/radix_sort_indices_by.hpp"

template <
    u32 key_bits,
    u32 capacity = 100'001,
    u32 skip_bits = 0,
    std::unsigned_integral I,
    typename Proj>
[[gnu::no_sanitize_address, gnu::flatten]] void
adaptive_sort_indices_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(key_bits > 0 && u64{skip_bits} + key_bits <= sizeof(Key) * 8);
    assert(n <= capacity);  // NOLINT

    if (n < 256)
    {
        const auto field = [&](const I& index)
        {
            if constexpr (key_bits == sizeof(Key) * 8)
            {
                return proj(index);
            }
            else
            {
                return (proj(index) >> skip_bits) & ((Key{1} << key_bits) - 1);
            }
        };
        std::ranges::sort(indices, indices + n, std::less{}, field);
    }
    else if (n < 1280)
    {
        radix_sort_indices_by<
            key_bits,
            8,
            SortOrder::Ascending,
            std::min(capacity, 1279u),
            skip_bits>(indices, n, proj);
    }
    else if (n < 8192)
    {
        radix_sort_indices_by<
            key_bits,
            10,
            SortOrder::Ascending,
            std::min(capacity, 8191u),
            skip_bits>(indices, n, proj);
    }
    else
    {
        radix_sort_indices_by<
            key_bits,
            13,
            SortOrder::Ascending,
            capacity,
            skip_bits>(indices, n, proj);
    }
}
