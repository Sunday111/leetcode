#pragma once

#include <algorithm>
#include <array>

[[nodiscard]] constexpr unsigned signature(int n) noexcept
{
    std::array<uint8_t, 10> f{};
    for (; n; n /= 10) ++f[(n % 10) & 0xFF];
    unsigned r = 0;
    for (auto cnt : f) r <<= 3, r |= cnt;
    return r;
}

class Solution
{
    static constexpr auto t = []
    {
        std::array<decltype(signature(1)), 30> r{};
        for (uint8_t i = 0; i != r.size(); ++i) r[i] = signature(1 << i);
        return r;
    }();

public:
    [[nodiscard]] static constexpr bool reorderedPowerOf2(int n) noexcept
    {
        return std::ranges::find(t, signature(n)) != t.end();
    }
};
