#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> triplets;
        std::ranges::sort(nums);

        auto a_end = std::ranges::upper_bound(nums, 0);
        for (auto a = std::ranges::lower_bound(
                 nums,
                 -(nums[nums.size() - 1] + nums[nums.size() - 2]));
             a != a_end;
             a = std::upper_bound(a, nums.end(), *a))
        {
            for (auto b = a + 1; b != nums.end();
                 b = std::upper_bound(b + 1, nums.end(), *b))
            {
                int s = -(*a + *b);
                auto c = std::lower_bound(b + 1, nums.end(), s);
                if (c != nums.end() && *c == s)
                {
                    triplets.emplace_back(std::vector<int>{*a, *b, *c});
                }
            }
        }

        return triplets;
    }
};
