#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"
#include "namespaces.hpp"
#include "swap_if_greater.hpp"

class Solution
{
public:
    [[nodiscard]] std::vector<int> getBiggestThree(
        std::vector<std::vector<int>>& grid) noexcept
    {
        auto& r = impl(reinterpret_cast<std::vector<std::vector<u32>>&>(grid));
        return std::move(reinterpret_cast<std::vector<int>&>(r));
    }

    [[nodiscard]] std::vector<u32>& impl(
        std::vector<std::vector<u32>>& grid) noexcept
    {
        u8 h = grid.size() & 0xFF, w = grid[0].size() & 0xFF, w1 = w - 1;
        u32 r[]{0, 0, 0};

        static u32 d1[4][50][51];
        for (u8 di = 0; di != h; ++di)
        {
            u8 dl = std::min<u8>(w, h - di);
            for (u8 j = 0; j != dl; ++j)
            {
                d1[0][di][j + 1] = d1[0][di][j] + grid[di + j][j];
                d1[2][di][j + 1] = d1[2][di][j] + grid[di + j][w1 - j];
            }
        }

        for (u8 di = 0; di != w; ++di)
        {
            u8 dl = std::min<u8>(w - di, h);
            for (u8 j = 0; j != dl; ++j)
            {
                d1[1][di][j + 1] = d1[1][di][j] + grid[j][di + j];
                d1[3][di][j + 1] = d1[3][di][j] + grid[j][w1 - (di + j)];
            }
        }

        auto visit = [&] [[gnu::always_inline]] (u32 s) noexcept
        {
            s &= -u32{s != r[0] && s != r[1] && s != r[2]};
            r[2] = std::max(r[2], s);
            swap_if_greater(r[2], r[1]);
            swap_if_greater(r[1], r[0]);
        };

        stdr::for_each(grid | stdv::join, visit);

        auto get_sum_a =
            [&] [[gnu::always_inline]] (u8 x, u8 y, u8 t) noexcept -> u32
        {
            if (x < y)
            {
                return d1[0][y - x][x + t] - d1[0][y - x][x];
            }
            else
            {
                return d1[1][x - y][y + t] - d1[1][x - y][y];
            }
        };

        auto get_sum_b =
            [&] [[gnu::always_inline]] (u8 x, u8 y, u8 t) noexcept -> u32
        {
            u8 xh = w - 1 - x;
            if (xh < y)
            {
                u8 di = y - xh;
                return d1[2][di][xh + t] - d1[2][di][xh];
            }
            else
            {
                u8 di = xh - y;
                return d1[3][di][y + t] - d1[3][di][y];
            }
        };

        const u8 max_side = std::min(w, h);
        const u8 lim_t = (max_side + (max_side & 1)) / 2;
        for (u8 t = 1; t != lim_t; ++t)
        {
            const u8 lim_y = h - t, lim_x = w - t;
            for (u8 y = t; y != lim_y; ++y)
            {
                for (u8 x = t; x != lim_x; ++x)
                {
                    visit(
                        get_sum_a(x, y - t, t) + get_sum_a(x - t, y, t) +
                        get_sum_b(x, y - t, t) + get_sum_b(x + t, y, t) +
                        grid[y + t][x] - grid[y - t][x]);
                }
            }
        }

        auto& v = grid[0];
        v.resize(3);
        u8 l = 0;
        v[l] = r[0], l += !!r[0];
        v[l] = r[1], l += !!r[1];
        v[l] = r[2], l += !!r[2];
        v.resize(l);
        return v;
    }
};

#include "sync_stdio.hpp"
