#pragma once

#include <cstdint>
#include <limits>

class Solution
{
public:
    static constexpr auto kMax = []
    {
        int64_t r = 1;
        while (r <= std::numeric_limits<int>::max()) r *= 3;
        return static_cast<int>(r / 3);
    }();
    [[nodiscard]] static constexpr bool isPowerOfThree(int n) noexcept
    {
        return n > 0 && !(kMax % n);
    }
};
