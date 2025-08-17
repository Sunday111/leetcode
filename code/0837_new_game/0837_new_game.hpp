#pragma once

#include <array>

class Solution
{
public:
    using u16 = uint16_t;

    [[nodiscard]] static constexpr double
    new21Game(u16 n, u16 k, u16 maxPts) noexcept
    {
        if (k == 0 || n >= k + maxPts) return 1;

        std::array<float, 20'002> dp{};
        constexpr u16 o = 10'001;
        dp[o] = 1, n += o + 1, k += o;

        double r = 0.0;
        float sum = 1.0, m = 1.f / static_cast<float>(maxPts);
        u16 i = o + 1, j = i - maxPts, mnk = std::min(n, k);

        for (; i != mnk; ++i, ++j)
        {
            dp[i] = m * sum;
            sum += dp[i] - dp[j];
        }

        for (; i != n; ++i, ++j)
        {
            dp[i] = m * sum;
            r += static_cast<double>(dp[i]);
            sum -= dp[j];
        }

        return r;
    }
};
