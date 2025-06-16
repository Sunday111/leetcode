#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> buildArray(
        const std::vector<int>& nums) noexcept
    {
        std::vector<int> r;
        r.reserve(nums.size());
        for (int v : nums)
        {
            r.push_back(nums[std::bit_cast<unsigned>(v)]);
        }
        return r;
    }
};
