#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::max(a, b);
};
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

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
