#pragma once

#include <bit>
#include <cstdint>
class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;
    static constexpr u32 kMOD = 1'000'000'007;
    [[nodiscard]] static constexpr u32 concatenatedBinary(u32 n) noexcept
    {
        u64 acc = 0;
        for (u32 i = 1; i <= n; ++i)
        {
            acc <<= 32 - std::countl_zero(i);
            acc |= i;
            if (acc >= kMOD) acc %= kMOD;
        }
        return static_cast<u32>(acc);
    }
};
