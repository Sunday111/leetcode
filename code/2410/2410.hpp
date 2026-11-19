#pragma once

#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr size_t matchPlayersAndTrainers(
        std::vector<int>& players,
        std::vector<int>& trainers) noexcept
    {
        radix_sort<u32, SortOrder::Descending, 6, 3>(
            reinterpret_range<u32>(players));
        radix_sort<u32, SortOrder::Descending, 8, 4>(
            reinterpret_range<u32>(trainers));

        const size_t np = players.size(), nt = trainers.size();
        size_t ip = 0, it = 0;
        while (ip != np && it != nt) it += players[ip++] <= trainers[it];

        return it;
    }
};
