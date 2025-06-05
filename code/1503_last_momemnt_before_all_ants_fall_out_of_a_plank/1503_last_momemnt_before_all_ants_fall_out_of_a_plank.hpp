#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int getLastMoment(
        int n,
        std::vector<int>& left,
        std::vector<int>& right) noexcept
    {
        int r = 0;
        if (left.size() > 0)
        {
            r = std::max(r, *std::ranges::max_element(left));
        }

        if (right.size() > 0)
        {
            r = std::max(r, n - *std::ranges::min_element(right));
        }

        return r;
    }
};
