#pragma once

#include <cmath>
#include <cstdint>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 bulbSwitch(u32 n) noexcept
    {
        return static_cast<u32>(std::sqrt(static_cast<double>(n)));
    }
};
