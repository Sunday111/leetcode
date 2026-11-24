#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstring>
#include <type_traits>

#include "integral_aliases.hpp"
#include "uint_for_value.hpp"

struct RadixSortIndicesByStorage
{
    template <std::unsigned_integral I, u32 capacity>
    inline static I scratch[capacity];

    alignas(u32) inline static u8 counts[sizeof(u32) << 16];
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    u32 capacity = 100'001,
    std::unsigned_integral I,
    typename Proj>
[[gnu::no_sanitize_address, gnu::flatten]] void
radix_sort_indices_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    using Count = UintForValue<capacity>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(bits_per_pass > 0 && bits_per_pass <= 16);

    constexpr u32 radix = 1u << bits_per_pass;
    constexpr Key mask = radix - 1;
    constexpr u32 max_passes =
        (sizeof(Key) * 8 + bits_per_pass - 1) / bits_per_pass;
    constexpr u32 passes = num_passes == 0xFFFFFFFF ? max_passes : num_passes;
    static_assert(passes <= max_passes);

    auto* counts = reinterpret_cast<Count*>(RadixSortIndicesByStorage::counts);
    assert(n <= capacity);  // NOLINT
    I* src = indices;
    I* dst = RadixSortIndicesByStorage::scratch<I, capacity>;

    for (u32 pass = 0; pass < passes; ++pass)
    {
        std::memset(counts, 0, radix * sizeof(Count));
        const u32 shift = pass * bits_per_pass;
        for (u32 pos = 0; pos < n; ++pos)
        {
            ++counts[(proj(src[pos]) >> shift) & mask];
        }

        for (u32 i = 1; i < radix; ++i)
        {
            counts[i] += counts[i - 1];
        }
        for (u32 pos = n; pos--;)
        {
            const I index = src[pos];
            const Key digit = (proj(index) >> shift) & mask;
            dst[--counts[digit]] = index;
        }
        std::swap(src, dst);
    }
    if (passes % 2 && n)
    {
        std::memcpy(indices, src, n * sizeof(I));
    }
}
