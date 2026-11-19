#pragma once

#include <bit>

#include "int_if.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 minimumOneBitOperations(u32 n) noexcept
    {
        u32 r = 0;
        for (u32 b = 0; n; b = !b, n ^= std::bit_floor(n))
        {
            r += negate_if(b, ~0u >> std::countl_zero(n));
        }
        return r;
    }
};
