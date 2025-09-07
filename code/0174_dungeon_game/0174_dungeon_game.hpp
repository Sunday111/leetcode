#pragma once

#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr int calculateMinimumHP(
        std::vector<std::vector<int>>& dungeon) noexcept
    {
        // w and h are in range [1; 200]
        const u8 h = dungeon.size() & 0xFF;
        const u8 w = dungeon[0].size() & 0xFF;
        const u8 last_x = w - 1;
        const u8 last_y = h - 1;

        // Init bottom right corner with required value
        dungeon[last_y][last_x] = std::max(1, 1 - dungeon[last_y][last_x]);

        // Bottom row
        for (u8 x = last_x; x--;)
        {
            const int& next = dungeon[last_y][x + 1];
            int& current = dungeon[last_y][x];
            current = std::max(1, next - current);
        }

        // Right column
        for (u8 y = last_y; y--;)
        {
            const int& next = dungeon[y + 1][last_x];
            int& current = dungeon[y][last_x];
            current = std::max(1, next - current);
        }

        // Fill the whole board. Right and bottom cells always exist
        for (u8 y = last_y; y--;)
        {
            auto& current_row = dungeon[y];
            auto& next_row = dungeon[y + 1];
            for (u8 x = last_x; x--;)
            {
                int& current = current_row[x];
                const int& right = current_row[x + 1];
                const int& bottom = next_row[x];
                current =
                    std::max(1, std::min(right - current, bottom - current));
            }
        }

        return dungeon[0][0];
    }
};
