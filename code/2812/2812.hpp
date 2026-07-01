#include <utility>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr u32 dx[4]{0u, -1u, 1u, 0u};
    inline static constexpr u32 dy[4]{-1u, 0u, 0u, 1u};
    inline static u32 q[2][400 * 400 + 1];
    inline static u16 g[401][401];

    [[gnu::always_inline]] static u32 pack(u32 x, u32 y) noexcept
    {
        return (x << 16) | y;
    }

    [[gnu::always_inline]] static std::pair<u32, u32> unpack(u32 p) noexcept
    {
        return {p >> 16, p & 0xFFFF};
    }

    inline static constexpr u32 kInf = 0xFFFFu >> 1;

    u16 maximumSafenessFactor(
        const std::vector<std::vector<int>>& ggg) const noexcept
    {
        auto& gg = reinterpret_cast<const std::vector<std::vector<u32>>&>(ggg);
        const u32 h = static_cast<u32>(gg.size());
        const u32 w = static_cast<u32>(gg.front().size());
        const u32 target = static_cast<u32>(pack(w - 1, h - 1));
        [[assume(h < 401)]];
        [[assume(w < 401)]];

        {
            u32 qe{};
            for (u32 y = 0; y != h; ++y)
            {
#pragma GCC unroll
                for (u32 x = 0; x != w; ++x)
                {
                    bool b = gg[y][x];
                    g[y][x] = kInf & -u32{!b};
                    q[0][qe] = pack(x, y);
                    qe += b;
                }
            }

            for (u32 qb = 0, d = 1; qb != qe; ++d)
            {
                for (u32 stop = qe; qb != stop; ++qb)
                {
                    auto [x, y] = unpack(q[0][qb]);
#pragma GCC unroll 4
                    for (u32 t = 0; t != 4; ++t)
                    {
                        u32 nx = std::min(x + dx[t], w);
                        u32 ny = std::min(y + dy[t], h);
                        bool b = (nx != w) & (ny != h) & (g[ny][nx] == kInf);
                        g[ny][nx] =
                            ((d & -u32{b}) | (g[ny][nx] & -u32{!b})) & 0xFFFF;
                        q[0][qe] = pack(nx, ny);
                        qe += b;
                    }
                }
            }
        }

        auto *curr = q[0], *next = q[1];
        u32 curr_end = 0, next_end = 0;

        curr[curr_end++] = pack(0, 0);
        u16 ans = std::min(g[0][0], g[h - 1][w - 1]);
        if (w > 1 && h > 1)
        {
            ans = std::min(ans, std::max(g[0][1], g[1][0]));
            ans = std::min(ans, std::max(g[h - 1][w - 2], g[h - 2][w - 1]));
        }
        g[0][0] |= 1u << 15;
        while (ans && curr_end)
        {
            while (curr_end)
            {
                --curr_end;
                [[unlikely]] if (curr[curr_end] == target)
                {
                    return ans;
                }
                auto [x, y] = unpack(curr[curr_end]);
#pragma GCC unroll 4
                for (u32 t = 0; t != 4; ++t)
                {
                    u32 nx = std::min(x + dx[t], w),
                        ny = std::min(y + dy[t], h);
                    auto nv = g[ny][nx];
                    bool u = (nx == w) | (ny == h) | (nv >> 15);
                    g[ny][nx] |= 1u << 15;
                    curr[curr_end] = next[next_end] = pack(nx, ny);
                    bool b = nv < ans;
                    curr_end += (!b) & (!u);
                    next_end += b & !u;
                }
            }

            std::swap(curr, next);
            std::swap(curr_end, next_end);
            --ans;
        }

        return ans;
    }
};

#include "sync_stdio.hpp"
