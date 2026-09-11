#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <functional>
#include <numeric>
#include <type_traits>

#include "integral_aliases.hpp"

template <u8 bits_per_pass, u32 capacity = 100'001, std::unsigned_integral I, typename Proj>
void radix_sort_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(bits_per_pass > 0 && bits_per_pass <= 16);

    constexpr u32 radix = 1u << bits_per_pass;
    constexpr Key mask = radix - 1;
    constexpr u32 passes = (sizeof(Key) * 8 + bits_per_pass - 1) / bits_per_pass;

    static std::array<I, capacity> scratch;
    std::array<u32, radix> counts{};
    assert(n <= capacity);

    for (u32 pass = 0; pass < passes; ++pass)
    {
        counts.fill(0);
        const u32 shift = pass * bits_per_pass;
        for (u32 pos = 0; pos < n; ++pos)
            ++counts[(std::invoke(proj, indices[pos]) >> shift) & mask];

        std::inclusive_scan(counts.begin(), counts.end(), counts.begin());
        for (u32 pos = n; pos--;)
        {
            const I index = indices[pos];
            const Key digit = (std::invoke(proj, index) >> shift) & mask;
            scratch[--counts[digit]] = index;
        }
        std::copy_n(scratch.data(), n, indices);
    }
}
