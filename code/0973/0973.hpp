#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> kClosest(
        std::vector<std::vector<int>>& points,
        int k)
    {
        std::ranges::sort(
            points,
            [](const std::vector<int>& a, const std::vector<int>& b)
            {
                int la = a[0] * a[0] + a[1] * a[1];
                int lb = b[0] * b[0] + b[1] * b[1];
                return la < lb;
            });

        points.resize(static_cast<size_t>(k));
        return points;
    }
};
