#include <vector>

#include "int_if.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr u32 dx[4]{0u, -1u, 1u, 0u};
    inline static constexpr u32 dy[4]{-1u, 0u, 0u, 1u};

    [[nodiscard, gnu::always_inline]] static constexpr u16 pack(
        u32 x,
        u32 y) noexcept
    {
        return ((x << 8) | y) & 0xffff;
    }

    [[nodiscard, gnu::always_inline]] static constexpr std::pair<u32, u32>
    unpack(u16 p) noexcept
    {
        return {p >> 8, p & 0xff};
    }

    constexpr bool findSafeWalk(
        const std::vector<std::vector<int>>& grid,
        u32 health) const noexcept
    {
        u8 qs = 0;
        u16 c[64][64], q[256];
        const u32 h = static_cast<u32>(grid.size());
        const u32 w = static_cast<u32>(grid[0].size());
        const u16 target = pack(w - 1, h - 1);
        for (u8 y = 0; y != h; ++y)
        {
            for (u16 x = 0; x != w; ++x)
            {
                u32 v = grid[y][x] & 1;
                c[y][x] = pack(v << 1, health);
            }
        }

        bool result = false;
        auto enqueue =
            [&] [[gnu::always_inline]] (u32 x, u32 y, u32 cost) noexcept
        {
            auto [vq, min_cost] = unpack(c[y][x]);
            u32 t = (vq >> 1) + cost;
            bool b = (x == w) | (y == h) | (t >= min_cost);
            c[y][x] = iif(b, c[y][x], pack(vq | 1, t));
            q[qs] = pack(x, y);
            result |= (target == q[qs]) & !b;
            qs += !(vq & 1) & !b;
        };

        enqueue(0, 0, 0);

        while (!((!qs) | result))
        {
            auto [x, y] = unpack(q[--qs]);
            auto [vq, min_cost] = unpack(c[y][x]);
            c[y][x] = pack(vq & 0b10, min_cost);

            for (u32 i = 0; i != 4; ++i)
            {
                u32 nx = std::min(w, x + dx[i]);
                u32 ny = std::min(h, y + dy[i]);
                enqueue(nx, ny, min_cost);
            }
        }

        return result;
    }
};

#include "sync_stdio.hpp"
