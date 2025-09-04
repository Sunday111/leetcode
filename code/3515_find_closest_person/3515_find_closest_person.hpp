#pragma once

#include <cstdint>
#include <cstdlib>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr auto findClosest(u8 x, u8 y, u8 z) noexcept
    {
        int a = std::abs(x - z), b = std::abs(y - z);
        return (a < b) + ((b < a) << 1);
    }
};
