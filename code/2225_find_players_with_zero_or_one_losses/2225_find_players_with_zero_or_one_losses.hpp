#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    static std::vector<std::vector<int>> findWinners(
        std::vector<std::vector<int>>& matches)
    {
        std::unordered_map<int, uint8_t> lost_battles;

        for (auto& match : matches)
        {
            int winner = match[0];
            int loser = match[1];

            lost_battles[winner];
            auto& loser_lost_battles = lost_battles[loser];
            loser_lost_battles = std::min<uint8_t>(2u, loser_lost_battles + 1);
        }

        std::vector<int> lost_none, lost_one;

        for (auto [player, losses] : lost_battles)
        {
            if (losses == 0) lost_none.push_back(player);
            if (losses == 1) lost_one.push_back(player);
        }

        std::ranges::sort(lost_none);
        std::ranges::sort(lost_one);

        return {std::move(lost_none), std::move(lost_one)};
    }
};
