#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::vector<int>> transpose(
        const std::vector<std::vector<int>>& matrix)
    {
        const size_t m = matrix.size(), n = matrix.front().size();
        std::vector<std::vector<int>> r(n, std::vector<int>(m));
        for (size_t y = 0; y != m; ++y)
        {
            for (size_t x = 0; x != n; ++x)
            {
                r[x][y] = matrix[y][x];
            }
        }
        return r;
    }
};
