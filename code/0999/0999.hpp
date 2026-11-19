#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int numRookCaptures(
        std::vector<std::vector<char>>& board)
    {
        constexpr size_t n = 8;
        size_t rook_x = 0, rook_y = 0;

        [&]
        {
            for (; rook_y != n; ++rook_y)
            {
                for (rook_x = 0; rook_x != n; ++rook_x)
                {
                    if (board[rook_y][rook_x] == 'R')
                    {
                        return;
                    }
                }
            }
        }();

        int result = 0;

        auto test_cell = [&](size_t x, size_t y)
        {
            auto c = board[y][x];
            if (c == '.') return false;
            if (c == 'p') ++result;
            return true;
        };

        // right
        for (size_t x = rook_x + 1; x != n; ++x)
        {
            if (test_cell(x, rook_y)) break;
        }

        // left
        for (size_t x = rook_x;;)
        {
            if (x == 0) break;
            --x;
            if (test_cell(x, rook_y)) break;
        }

        // down
        for (size_t y = rook_y + 1; y != n; ++y)
        {
            if (test_cell(rook_x, y)) break;
        }

        // up
        for (size_t y = rook_y;;)
        {
            if (y == 0) break;
            --y;
            if (test_cell(rook_x, y)) break;
        }

        return result;
    }
};
