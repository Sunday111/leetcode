#pragma once

#include <cstdint>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr u8 numberOfMatches(u8 n) noexcept
    {
        return n - 1;
    }
};
