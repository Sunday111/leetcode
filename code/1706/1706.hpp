#pragma once

#include <ranges>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr std::vector<int> findBall(
        const std::vector<std::vector<int>>& grid) noexcept
    {
        const u8 h = grid.size() & 0xFF;
        const u8 w = grid.front().size() & 0xFF;
        std::vector<int> r(w, -1);
        for (const u8 start_x : std::views::iota(u8{0}, w))
        {
            u8 x = start_x, y = 0;
            while (true)
            {
                auto dx = grid[y][x];
                if (dx < 0 && x == 0) break;
                x += dx;
                if (dx > 0 && x == w) break;
                if (dx != grid[y][x]) break;
                if (++y == h)
                {
                    r[start_x] = x;
                    break;
                }
            }
        }

        return r;
    }
};
