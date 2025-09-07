#pragma once

#include <array>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

#define FORCE_INLINE inline __attribute__((always_inline))

[[nodiscard]] FORCE_INLINE constexpr u8 num_divs(u32 x) noexcept
{
    return (16 - (std::countl_zero(x) / 2)) & 0xFF;
}

inline constexpr auto kSums = []
{
    std::array<u64, 17> counts{};

    for (u8 i = 1; i != 17; ++i)
    {
        u64 x = u64{1} << 2 * (i - 1);
        u64 y = u64{1} << 2 * i;
        counts[i] = u64{num_divs(x & 0xFFFFFFFF)} * u64{y - x};
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
            u32 a = static_cast<u32>(query[0]);
            u32 b = static_cast<u32>(query[1]);
            u8 ka = num_divs(a);
            u8 kb = num_divs(b);
            u32 left = 1u << (ka - 1) * 2;
            u32 right = (1u << kb * 2) - 1;
            u64 excess_left = u64{a - left} * ka;
            u64 excess_right = u64{right - b} * kb;
            u64 sum = kSums[ka][kb] - excess_left - excess_right;
            r += sum / 2 + sum % 2;
        }
        return r;
    }
};
