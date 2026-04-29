#include <algorithm>
#include <ranges>
#include <vector>

#include "integral_aliases.hpp"
#include "upd_max.hpp"

class Solution
{
public:
    [[nodiscard]] u64 maximumScore(
        const std::vector<std::vector<int>>& g) const noexcept
    {
        return impl(reinterpret_cast<const std::vector<std::vector<u32>>&>(g));
    }

    [[nodiscard]] static u64 impl(
        const std::vector<std::vector<u32>>& g) noexcept
    {
        const u32 n = static_cast<u32>(g.size()), n1 = n + 1;
        static u64 s[2][101], dp[2][101][2];
        memset(dp[0], 0, 16 * n1);
        s[0][0] = s[1][0] = 0;
        for (u32 i = 0; i != n; i++)
        {
            s[0][i + 1] = s[0][i] + g[i][0];
        }

        bool t = 1;
        for (u32 c = 0; c < n - 1; c++)
        {
            for (u32 i = 0; i != n; i++)
            {
                s[t][i + 1] = s[t][i] + g[i][c + 1];
            }

            u64 pm = dp[!t][0][1];
            for (u32 nb = 1; nb != n1; nb++)
            {
                dp[t][nb][0] = dp[t][nb][1] =
                    max2(dp[!t][nb][0], pm + s[!t][nb]);
                upd_max(pm, dp[!t][nb][1] - std::min(dp[!t][nb][1], s[!t][nb]));
            }

            u64 sm = dp[!t][n][0] + s[t][n];
            for (u32 nb = n - 1; nb; nb--)
            {
                upd_max(dp[t][nb][0], sm - s[t][nb]);
                sm = max2(sm, dp[!t][nb][0] + s[t][nb]);
            }

            dp[t][0][0] = sm;
            dp[t][0][1] = max2(dp[!t][0][0], dp[!t][n][0]);
            t = !t;
        }

        return std::ranges::max(
            dp[!t] | std::views::take(n1) | std::views::join);
    }
};
