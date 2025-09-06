#pragma once

#include <array>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

#define FORCE_INLINE inline __attribute__((always_inline))

[[nodiscard]] FORCE_INLINE constexpr u8 count_divisions(u32 x) noexcept
{
    return (16 - (std::countl_zero(x) / 2)) & 0xFF;
}

inline constexpr auto kSums = []
{
    std::array<u64, 17> counts{};

    u32 x = 1;
    for (u8 i = 1; i != 17; ++i)
    {
        counts[i] = u64{count_divisions(x)} * u64{(x << 2) - x};
        x <<= 2;
    }

    std::array<std::array<u64, 17>, 17> table{};

    for (u8 ka = 1; ka != 17; ++ka)
    {
        u64 s = 0;
        for (u8 kb = ka; kb != 17; ++kb)
        {
            s += counts[kb];
            table[ka][kb] = s;
        }
    }

    return table;
}();

class Solution
{
public:
    [[nodiscard]] static constexpr u64 minOperations(
        const std::vector<std::vector<int>>& queries) noexcept

    {
        u64 r = 0;
        for (const auto& query : queries)
        {
            const u32 a = static_cast<u32>(query[0]);
            const u32 b = static_cast<u32>(query[1]);
            const u8 ka = count_divisions(a);
            const u8 kb = count_divisions(b);
            const u32 loa = 1u << (ka - 1) * 2;
            const u32 hib = 1u << (kb) * 2;
            const u64 total_divisions =
                kSums[ka][kb] -
                ((u64{a - loa} * ka) + (u64{hib - (b + 1)} * kb));
            r += total_divisions / 2 + total_divisions % 2;
        }
        return r;
    }
};
