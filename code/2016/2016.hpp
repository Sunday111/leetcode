#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int maximumDifference(
        std::vector<int>& nums) noexcept
    {
        int min_value = nums[0], r = -1;
        for (size_t i = 1; i != nums.size(); ++i)
        {
            int value = nums[i];
            int diff = value - min_value;
            if (diff > 0)
            {
                r = std::max(r, diff);
            }
            else
            {
                min_value = value;
            }
        }
        return r;
    }
};
