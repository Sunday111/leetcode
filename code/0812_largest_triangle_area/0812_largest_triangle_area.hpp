#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr double largestTriangleArea(
        const std::vector<std::vector<int>>& points) noexcept
    {
        int r = 0;
        for (auto& p1 : points)
        {
            const int x1 = p1[0], y1 = p1[1];
            for (auto& p2 : points)
            {
                const int x2 = p2[0], y2 = p2[1];
                for (auto& p3 : points)
                {
                    const int x3 = p3[0], y3 = p3[1];
                    r = std::max(
                        r,
                        std::abs(
                            x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
                }
            }
        }
        return static_cast<double>(r) / 2;
    }
};
