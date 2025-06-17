#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int findFinalValue(
        const std::vector<int>& nums,
        int original) noexcept
    {
        int r = original;
        while (std::ranges::find(nums, r) != nums.end())
        {
            r *= 2;
        }

        return r;
    }
};
