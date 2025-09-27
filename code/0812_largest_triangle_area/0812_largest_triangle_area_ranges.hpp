#pragma once

#include <ranges>
#include <vector>

class Solution
{
public:
    [[nodiscard]] inline static constexpr auto toPoint(
        const std::vector<int>& v) noexcept
    {
        return std::pair{v[0], v[1]};
    }

    [[nodiscard]] inline static constexpr auto toPoints(
        const std::vector<std::vector<int>>& arrays) noexcept
    {
        return arrays | std::views::transform(toPoint);
    }

    [[nodiscard]] static constexpr float largestTriangleArea(
        const std::vector<std::vector<int>>& points) noexcept
    {
        int r = 0;
        for (auto [ax, ay] : toPoints(points))
        {
            for (auto [bx, by] : toPoints(points))
            {
                for (auto [cx, cy] : toPoints(points))
                {
                    int t1 = ax * (by - cy);
                    int t2 = bx * (cy - ay);
                    int t3 = cx * (ay - by);
                    r = std::max(r, std::abs(t1 + t2 + t3));
                }
            }
        }
        return static_cast<float>(r) / 2;
    }
};
