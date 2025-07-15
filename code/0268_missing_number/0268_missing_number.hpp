#pragma once

#include <numeric>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int missingNumber(
        const std::vector<int>& nums) noexcept
    {
        const int n = static_cast<int>(nums.size());
        return ((1 + n) * n) / 2 - std::accumulate(nums.begin(), nums.end(), 0);
    }
};
