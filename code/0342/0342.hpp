#pragma once

#include <bit>

class Solution
{
public:
    [[nodiscard]] static constexpr bool isPowerOfFour(int n) noexcept
    {
        auto u = static_cast<unsigned>(n * (n > 0));
        return std::popcount(u) == 1 && !(std::countr_zero(u) % 2);
    }
};
