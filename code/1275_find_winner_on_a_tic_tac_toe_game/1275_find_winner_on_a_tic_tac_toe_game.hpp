#pragma once

#include <bitset>
#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string tictactoe(
        std::vector<std::vector<int>>& moves) noexcept
    {
        constexpr std::array win_states{
            std::bitset<9>(0b000000111),
            std::bitset<9>(0b000111000),
            std::bitset<9>(0b111000000),
            std::bitset<9>(0b001001001),
            std::bitset<9>(0b010010010),
            std::bitset<9>(0b100100100),
            std::bitset<9>(0b100010001),
            std::bitset<9>(0b001010100),
        };

        std::bitset<9> a, b;

        auto current = &a, next = &b;
        for (const auto& move : moves)
        {
            const int y = move[0], x = move[1];
            const uint8_t idx = (y * 3 + x) & 0XFF;
            current->set(idx, true);
            std::swap(current, next);
        }

        for (auto win_state : win_states)
        {
            if ((a & win_state).count() == 3) return "A";
            if ((b & win_state).count() == 3) return "B";
        }

        if ((a | b).count() == 9)
        {
            return "Draw";
        }

        return "Pending";
    }
};
