#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::vector<int>> shiftGrid(
        std::vector<std::vector<int>>& grid,
        uint16_t k) noexcept
    {
        const uint16_t rows = grid.size() & 0xFFFF;
        const uint16_t columns = grid.front().size() & 0xFFFF;
        const uint16_t n = rows * columns;
        k %= n;
        if (!k) return grid;

        std::vector<std::vector<int>> r(rows, std::vector<int>(columns));
        const uint16_t jump = n - k;

        for (uint16_t y = 0; y != rows; ++y)
        {
            uint16_t offset = y * columns + jump;
            for (uint16_t x = 0; x != columns; ++x)
            {
                uint16_t src_index = (offset + x) % n;
                r[y][x] = grid[src_index / columns][src_index % columns];
            }
        }

        return r;
    }
};
