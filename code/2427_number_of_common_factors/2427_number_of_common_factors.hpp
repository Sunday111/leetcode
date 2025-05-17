#pragma once

#include <cstdint>
#include <numeric>

class Solution
{
public:
    [[nodiscard]] static constexpr uint32_t commonFactors(
        uint32_t a,
        uint32_t b) noexcept
    {
        uint32_t r = 1;
        for (uint32_t i = std::gcd(a, b); i != 1; --i)
        {
            if ((a % i == 0) && (b % i == 0))
            {
                ++r;
            }
        }
        return r;
    }
};
