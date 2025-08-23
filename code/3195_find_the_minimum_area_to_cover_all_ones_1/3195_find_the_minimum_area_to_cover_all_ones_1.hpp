#pragma once

#include <vector>

#include "min_max_int.hpp"

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr int minimumArea(
        const std::vector<std::vector<int>>& grid) noexcept
    {
        const u16 h = grid.size() & 0xFFFF, w = grid.front().size() & 0xFFFF;
        u16 min_x = w - 1, min_y = h - 1, max_x = 0, max_y = 0;
        for (u16 y = 0; y != h; ++y)
        {
            auto& r = grid[y];
            bool has_some = false;
            // for (u16 x = 0; x != w; ++x)
            // {
            //     has_some |= r[x];
            //     min_x = iif(r[x], int_min(min_x, x), min_x);
            //     max_x = iif(r[x], int_max(max_x, x), max_x);
            // }

            for (u16 x = 0; x != min_x; ++x)
            {
                if (r[x])
                {
                    has_some = true;
                    min_x = x;
                    break;
                }
            }

            max_x = int_max(max_x, min_x);
            for (u16 x = w - 1; x > max_x; --x)
            {
                if (r[x])
                {
                    has_some = true;
                    max_x = x;
                    break;
                }
            }

            if (!has_some)
            {
                for (u16 x = min_x; x <= max_x; ++x)
                {
                    if (r[x])
                    {
                        has_some = true;
                        break;
                    }
                }
            }

            min_y = iif(has_some, int_min(min_y, y), min_y);
            max_y = iif(has_some, y, max_y);
        }

        return static_cast<int>((max_x - min_x) + 1) *
               static_cast<int>((max_y - min_y) + 1);
    }
};
