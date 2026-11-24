#pragma once

#include <utility>
#include <vector>

#include "int_if.hpp"
#include "minmax/max2.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int longestSubarray(
        const std::vector<int>& nums) noexcept
    {
        int l0 = 0, l1 = 0, r = 0;
        for (int v : nums)
        {
            l0 = iif(v, l0, l1);
            l1 = iif(v, l1 + 1, 0);
            r = max2(r, l0 + l1);
        }

        return r - std::cmp_equal(l1, nums.size());
    }
};
