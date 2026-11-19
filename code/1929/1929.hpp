#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> getConcatenation(
        const std::vector<int>& nums) noexcept
    {
        std::vector<int> r;
        r.reserve(2 * nums.size());
        auto it = std::back_inserter(r);
        std::ranges::copy(nums, it);
        std::ranges::copy(nums, it);
        return r;
    }
};
