#include <algorithm>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

class Solution
{
public:
    static constexpr u16 NN = 80 * (1u << 7);

    FORCE_INLINE static u16 idx(u8 i, u8 j) noexcept
    {
        return ((u16{i} << 7) | j) & 0xFFFF;
    }

    static u32 minCost(const std::vector<std::vector<u32>>& grid, u8 k)
    {
        const u16 M = 10'001;
        const u32 INF = 1'000'000'007;

        static u16 xList[M], nxt[NN];
        static u32 dp[2][NN];
        static u32 suffixMin[M];

        const u8 r = grid.size() & 0xFF;
        const u8 c = grid[0].size() & 0xFF;

        if (xList[0] != 0xFFFF) std::fill_n(xList, M, 0xFFFF);

        u16 xMax = 0;
        for (u8 i = 0; i != r; ++i)
        {
            for (u8 j = 0; j != c; ++j)
            {
                const u16 x = static_cast<u16>(grid[i][j]);
                const u16 p = idx(i, j);
                nxt[p] = xList[x];
                xList[x] = p;
                if (x > xMax) xMax = x;
            }
        }

        std::fill(dp[0], dp[0] + NN, INF);
        dp[0][idx(0, 0)] = 0;

        // Initial DP
        for (u8 i = 0; i != r; ++i)
        {
            for (u8 j = 0; j != c; ++j)
            {
                const u16 pos = idx(i, j);
                if (i > 0)
                {
                    dp[0][pos] =
                        std::min(dp[0][pos], dp[0][idx(i - 1, j)] + grid[i][j]);
                }

                if (j > 0)
                {
                    dp[0][pos] =
                        std::min(dp[0][pos], dp[0][idx(i, j - 1)] + grid[i][j]);
                }
            }
        }

        for (u8 t = 1; t <= k; ++t)
        {
            const bool curr = t & 1;
            const bool prev = (t - 1) & 1;

            u32 currMin = INF;
            for (u16 x = xMax; x != 0xFFFF; --x)
            {
                for (u16 e = xList[x]; e != 0xFFFF; e = nxt[e])
                {
                    currMin = std::min(currMin, dp[prev][e]);
                }
                suffixMin[x] = currMin;
            }

            for (u8 i = 0; i != r; ++i)
            {
                for (u8 j = 0; j != c; ++j)
                {
                    const u16 pos = idx(i, j);
                    const u32 x = grid[i][j];

                    u32 best = std::min(dp[prev][pos], suffixMin[x]);

                    if (i > 0)
                    {
                        best = std::min(best, dp[curr][idx(i - 1, j)] + x);
                    }

                    if (j > 0)
                    {
                        best = std::min(best, dp[curr][idx(i, j - 1)] + x);
                    }

                    dp[curr][pos] = best;
                }
            }
        }

        std::fill_n(xList, xMax + 1, 0xFFFF);
        return dp[k & 1][idx(r - 1, c - 1)];
    }

    [[nodiscard]] u32 minCost(
        const std::vector<std::vector<int>>& grid,
        u8 k) noexcept
    {
        return minCost(
            reinterpret_cast<const std::vector<std::vector<u32>>&>(grid),
            k);
    }
};
