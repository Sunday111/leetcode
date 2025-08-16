#pragma once

#include <bit>

class Solution
{
public:
    [[nodiscard]] static constexpr bool isPowerOfTwo(int n) noexcept
    {
        return n > 0 && std::popcount(std::bit_cast<unsigned>(n)) == 1;
    }
};
