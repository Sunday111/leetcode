#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> createTargetArray(
        std::vector<int>& nums,
        std::vector<int>& index) noexcept
    {
        std::vector<int> r;
        r.reserve(nums.size());

        for (size_t i = 0; i != nums.size(); ++i)
        {
            r.insert(std::next(r.begin(), index[i]), nums[i]);
        }

        return r;
    }
};
