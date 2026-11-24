#pragma once

#include <vector>

#include "radix_sort/radix_sort.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr size_t matchPlayersAndTrainers(
        std::vector<int>& players,
        std::vector<int>& trainers) noexcept
    {
        radix_sort<6, 3, SortOrder::Descending>(
            reinterpret_cast<u32*>(players.data()),
            static_cast<u32>(players.size()));
        radix_sort<8, 4, SortOrder::Descending>(
            reinterpret_cast<u32*>(trainers.data()),
            static_cast<u32>(trainers.size()));

        const size_t np = players.size(), nt = trainers.size();
        size_t ip = 0, it = 0;
        while (ip != np && it != nt) it += players[ip++] <= trainers[it];

        return it;
    }
};
