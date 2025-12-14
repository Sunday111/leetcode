#include <cstdint>
#include <vector>

using u32 = uint32_t;

class Solution
{
public:
    [[nodiscard]] static int uniquePathsWithObstacles(
        std::vector<std::vector<int>>& g) noexcept
    {
        const u32 h = static_cast<u32>(g.size());
        const u32 w = static_cast<u32>(g[0].size());

        g[0][0] = !g[0][0];
        for (u32 x = 1; x != w; ++x) g[0][x] = !g[0][x] && g[0][x - 1];

        for (u32 y = 1; y != h; ++y)
        {
            auto &prev = g[y - 1], &curr = g[y];
            curr[0] = !curr[0] && prev[0];
            for (u32 x = 1; x != w; ++x)
            {
                curr[x] = ((curr[x - 1] + prev[x]) & -!curr[x]);
            }
        }

        return g[h - 1][w - 1];
    }
};
