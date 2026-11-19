#pragma once

#include <algorithm>
#include <functional>
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

        auto sortDiag = [&]<typename Cmp>(Cmp&& cmp, u8 start_x, u8 start_y)
        {
            const u8 l = (n - std::max(start_x, start_y)) & 0xFF;
            std::ranges::sort(
                std::views::iota(u8{0}, l) |
                    std::views::transform(
                        [&](u8 i) -> int&
                        { return grid[start_y + i][start_x + i]; }),
                std::forward<Cmp>(cmp));
        };

        // Bottom-left
        std::ranges::for_each(
            std::views::iota(u8{0}, n) | std::views::reverse,
            std::bind(sortDiag, std::greater{}, 0, std::placeholders::_1));

        // Top-right
        std::ranges::for_each(
            std::views::iota(u8{1}, n),
            std::bind(sortDiag, std::less{}, std::placeholders::_1, 0));

        return std::move(grid);
    }
};

static_assert(
    []()
    {
        std::vector<std::vector<int>> grid{{1, 7, 3}, {9, 8, 2}, {4, 5, 6}};
        std::vector<std::vector<int>> expected{{8, 2, 3}, {9, 6, 7}, {4, 5, 1}};
        return Solution{}.sortMatrix(grid) == expected;
    }());
