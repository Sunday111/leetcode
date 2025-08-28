#pragma once

#include <algorithm>
#include <span>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr std::vector<std::vector<int>> sortMatrix(
        std::vector<std::vector<int>>& grid) noexcept
    {
        u8 n = grid.size() & 0xFF;

        std::array<int, 10> a;  // NOLINT

        // Bottom-left
        for (u8 start_y = 0; start_y != n; ++start_y)
        {
            for (u8 y = start_y, x = 0; y != n; ++y, ++x) a[x] = grid[y][x];
            std::ranges::sort(std::span{a}.first(n - start_y), std::greater{});
            for (u8 y = start_y, x = 0; y != n; ++y, ++x) grid[y][x] = a[x];
        }

        // Top-right
        for (u8 start_x = 1; start_x != n; ++start_x)
        {
            for (u8 y = 0, x = start_x; x != n; ++y, ++x) a[y] = grid[y][x];
            std::ranges::sort(std::span{a}.first(n - start_x), std::less{});
            for (u8 y = 0, x = start_x; x != n; ++y, ++x) grid[y][x] = a[y];
        }

        return std::move(grid);
    }
};
