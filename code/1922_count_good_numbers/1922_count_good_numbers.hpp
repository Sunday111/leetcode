#pragma once

#include "mod_int.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 countGoodNumbers(u64 n) noexcept
    {
        const u64 odd = n / 2, even = n - odd;
        return (ModInt{4}.pow(odd) * ModInt{5}.pow(even)).value;
    }
};
