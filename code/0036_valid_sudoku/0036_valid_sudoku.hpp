#pragma once

#include <array>
#include <bitset>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr bool isValidSudoku(
        const std::vector<std::vector<char>>& board) noexcept
    {
        std::array<std::bitset<9>, 9> h, v, b;
        for (u8 y = 0; y != 9; ++y)
        {
            for (u8 x = 0; x != 9; ++x)
            {
                if (char c = board[y][x]; c != '.')
                {
                    u8 i = c - '0', t = (y / 3) * 3 + x / 3;
                    if (h[y][i] || v[x][i] || b[t][i]) return false;
                    h[y][i] = v[x][i] = b[t][i] = true;
                }
            }
        }
        return true;
    }
};
