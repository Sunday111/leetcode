#include <algorithm>
#include <cstring>
#include <vector>

#include "integral_aliases.hpp"
#include "max2.hpp"
#include "sync_stdio.hpp"

class Solution
{
public:
    inline static u16 dp[2][72][72];
    [[gnu::target("avx2")]]
    u16 cherryPickup(const std::vector<std::vector<int>>& g) noexcept
    {
        const u8 w = g[0].size() & 255, height = g.size() & 255;
        std::memset(dp, 0, sizeof dp);

        dp[0][1][w] = (g[0][0] + g[0][w - 1]) & 255;

        u16 a = dp[0][1][w];
        for (u8 y = 1; y != height; ++y)
        {
            auto& curr = dp[y & 1];
            const auto& prev = dp[(y + 1) & 1];
            const auto& row = g[y];
            u8 lim_i = std::min(y + 1, w - 1) & 127;
            for (u8 i = 0; i != lim_i; ++i)
            {
                u8 lim_j = std::max(i + 1, w - std::min<int>(w, y + 1)) & 127;
                for (u8 j = lim_j; j != w; ++j)
                {
                    [[assume(i < 70)]];
                    [[assume(j < 70)]];
                    const u16 p[]{
                        max2(prev[i][j], prev[i][j + 1]),
                        max2(prev[i][j + 2], prev[i + 1][j]),
                        max2(prev[i + 1][j + 2], prev[i + 2][j]),
                        max2(prev[i + 2][j + 1], prev[i + 2][j + 2]),
                    };
                    const u16 h[]{
                        max2(p[0], p[1]),
                        max2(p[2], p[3]),
                    };
                    const u16 s = max2(max2(h[0], h[1]), prev[i + 1][j + 1]) +
                                  ((row[i] + row[j]) & 255);
                    curr[i + 1][j + 1] = s;
                    a = max2(a, s);
                }
            }
        }

        return a;
    }
};
