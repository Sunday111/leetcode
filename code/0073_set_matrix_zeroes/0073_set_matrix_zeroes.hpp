#pragma once

#include <algorithm>
#include <bitset>
#include <vector>

class Solution
{
public:
    void setZeroes(std::vector<std::vector<int>>& matrix)
    {
        const size_t rows = matrix.size();
        const size_t columns = matrix.front().size();

        std::bitset<200> zero_rows, zero_columns;
        for (size_t y = 0; y != rows; ++y)
        {
            for (size_t x = 0; x != columns; ++x)
            {
                if (matrix[y][x] == 0)
                {
                    zero_rows[y] = true;
                    zero_columns[x] = true;
                }
            }
        }

        for (size_t y = 0; y != rows; ++y)
        {
            if (auto& row = matrix[y]; zero_rows[y])
            {
                std::ranges::fill(row, 0);
            }
            else
            {
                for (size_t x = 0; x != columns; ++x)
                {
                    if (zero_columns[x]) row[x] = 0;
                }
            }
        }
    }
};
