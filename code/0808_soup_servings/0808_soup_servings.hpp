#pragma once

#include <array>

class Solution
{
public:
    using u8 = uint8_t;
    u8 n = 0, a = 0, b = 0;
    std::array<std::array<float, 192>, 192> dp{};

    [[nodiscard]] float solve() noexcept
    {
        if (a >= n && b >= n) return 0.5;
        if (a >= n) return 1;
        if (b >= n) return 0;
        float& r = dp[a][b];
        if (r == 0.0f)
        {
            a += 4, r += solve();
            --a, ++b, r += solve();
            --a, ++b, r += solve();
            --a, ++b, r += solve();
            --a, b -= 3;
            r /= 4;
        }
        return r;
    }

    [[nodiscard]] float soupServings(int n_) noexcept
    {
        if (n_ >= 4800) return 1.0;
        n_ = (n_ + 24) / 25;
        n = n_ & 0xFF;
        return solve();
    }
};
