#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int areaOfMaxDiagonal(
        std::vector<std::vector<int>>& sizes) noexcept
    {
        int max_diag_sq = 0, max_area = 0;
        for (auto& s : sizes)
        {
            int a = s[0], b = s[1];
            int diag_sq = a * a + b * b, area = a * b;
            if (diag_sq > max_diag_sq ||
                (diag_sq == max_diag_sq && area > max_area))
            {
                max_diag_sq = diag_sq;
                max_area = area;
            }
        }

        return max_area;
    }
};
