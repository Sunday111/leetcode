#pragma once

#include <ranges>
#include <vector>

class Solution
{
public:
    std::vector<bool> prefixesDivBy5(const std::vector<int>& nums)
    {
        return std::ranges::to<std::vector>(
            nums | std::views::transform(
                       [x = 0](int v) mutable
                       {
                           x = (x << 1) | (v & 1);
                           x -= 5 & -(x > 4);
                           return !x;
                       }));
    }
};
