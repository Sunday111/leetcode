#pragma once

#include <algorithm>
#include <ranges>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr std::vector<std::vector<int>> sortMatrix(
        std::vector<std::vector<int>>& grid) noexcept
    {
        const u8 n = grid.size() & 0xFF;

        // Bottom-left
        for (u8 start_y = 0; start_y != n; ++start_y)
        {
            u8 l = n - start_y;
            std::ranges::sort(
                std::views::iota(u8{0}, u8{l}) |
                    std::views::transform(
                        [&](u8 i) -> int& { return grid[start_y + i][i]; }),
                std::greater{});
        }

        // Top-right
        for (u8 start_x = 1; start_x != n; ++start_x)
        {
            u8 l = n - start_x;
            std::ranges::sort(
                std::views::iota(u8{0}, u8{l}) |
                    std::views::transform(
                        [&](u8 i) -> int& { return grid[i][start_x + i]; }),
                std::less{});
        }

        return std::move(grid);
    }
};
