#pragma once

#include <algorithm>
#include <array>

[[nodiscard]] constexpr std::array<uint8_t, 10> freq(int n) noexcept
{
    std::array<uint8_t, 10> f{};
    for (; n; n /= 10) ++f[(n % 10) & 0xFF];
    return f;
}

class Solution
{
    static constexpr auto t = []
    {
        std::array<std::array<uint8_t, 10>, 31> r{};
        for (uint8_t i = 0; i != 31; ++i) r[i] = freq(1 << i);
        return r;
    }();

public:
    [[nodiscard]] static constexpr bool reorderedPowerOf2(int n) noexcept
    {
        return std::ranges::find(t, freq(n)) != t.end();
    }
};
