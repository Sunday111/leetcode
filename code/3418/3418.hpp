#include <vector>

#include "max4.hpp"

class Solution
{
public:
    [[nodiscard, gnu::target("avx2,bmi2")]] constexpr int maximumAmount(
        const std::vector<std::vector<int>>& g) noexcept
    {
        int dp[500][3];
        using Idx = uint32_t;
        const auto w = static_cast<Idx>(g[0].size());
        [[assume(w < 501)]];

        std::fill_n(dp[1], 3 * (w - 1), -500'000);
        dp[0][0] = dp[0][1] = dp[0][2] = 0;

        for (const auto& row : g)
        {
            // Variable names:
            // c: current cell
            // l: left cell
            // t: top cell
            // a: value at current cell
            // b: value if ability is used

            // Handle the first cell manually
            // as there is no left cell
            {
                auto c = dp[0];
                int t[]{c[0], c[1], c[2]};
                int a = row[0], b = max2(a, 0);
                c[0] = a + t[0];
                c[1] = max2(a + t[1], b + t[0]);
                c[2] = max2(a + t[2], b + t[1]);
            }

            for (Idx x = 1; x != w; ++x)
            {
                auto c = dp[x], l = dp[x - 1];
                int t[]{c[0], c[1], c[2]};
                int a = row[x], b = max2(a, 0);
                c[0] = max2(a + l[0], a + t[0]);
                c[1] = max4(a + l[1], a + t[1], b + l[0], b + t[0]);
                c[2] = max4(a + l[2], a + t[2], b + l[1], b + t[1]);
            }
        }

        return dp[w - 1][2];
    }
};
