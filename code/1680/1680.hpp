#pragma once

#include <array>
#include <bit>
#include <integral_aliases.hpp>

class Solution
{
public:
    inline static const auto kAns = []  // NOLINT
    {
        std::array<u32, 100'001> r;  // NOLINT
        constexpr u32 kMOD = 1'000'000'007;

        for (u32 i = 1; i != r.size(); ++i)
        {
            u64 x = r[i - 1];
            x <<= std::bit_width(i);
            x |= i;
            if (x >= kMOD) x %= kMOD;
            r[i] = static_cast<u32>(x);
        }

        return r;
    }();

    [[nodiscard]] static constexpr auto concatenatedBinary(u32 n) noexcept
    {
        return kAns[n];
    }
};
