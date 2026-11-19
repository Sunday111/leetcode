#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr int getWinner(
        std::vector<int>& arr,
        u32 k) noexcept
    {
        const u32 n = arr.size() & 0xFFFFFFFF;
        u32 wins = 0;
        int winner = arr.front();

        for (uint32_t i = 1; i != n && wins != k; ++i)
        {
            int vi = arr[i];
            if (winner > vi)
            {
                ++wins;
            }
            else
            {
                wins = 1;
                winner = vi;
            }
        }

        return winner;
    }
};
