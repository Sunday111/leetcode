#pragma once

#include <vector>

class Solution
{
public:
    static int minSubArrayLen(const int target, const std::vector<int>& nums)
    {
        size_t l = 0, r = 1;
        int sum = nums.front();
        size_t min_length = nums.size() + 1;

        while (l != nums.size())
        {
            if (sum < target)
            {
                if (r == nums.size()) break;
                sum += nums[r++];
            }
            else
            {
                sum -= nums[l];
                if (auto dist = r - l; dist < min_length)
                {
                    min_length = dist;
                }
                ++l;
            }
        }

        if (min_length > nums.size()) return 0;
        return static_cast<int>(min_length);
    }
};
