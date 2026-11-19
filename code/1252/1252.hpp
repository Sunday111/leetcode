#pragma once

#include <bitset>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int oddCells(
        size_t m,
        size_t n,
        [[maybe_unused]] const std::vector<std::vector<int>>& indices) noexcept
    {
        std::bitset<50> odd_rows, odd_columns;

        for (auto& coord : indices)
        {
            odd_rows.flip(static_cast<size_t>(coord[0]));
            odd_columns.flip(static_cast<size_t>(coord[1]));
        }

        size_t num_odd_rows = odd_rows.count();
        size_t num_odd_columns = odd_columns.count();

        return static_cast<int>(
            (num_odd_rows * n + num_odd_columns * (m - num_odd_rows)) -
            num_odd_columns * num_odd_rows);
    }
};
