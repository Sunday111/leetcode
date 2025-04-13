#pragma once

#include <vector>

class Solution
{
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums)
    {
        std::vector<int> result = nums;

        int prev_prod = 1;
        for (int& v : result)
        {
            prev_prod *= std::exchange(v, prev_prod);
        }

        prev_prod = 1;

        size_t i = nums.size();
        do
        {
            --i;
            result[i] *= prev_prod;
            prev_prod *= nums[i];
        } while (i != 0);

        return result;
    }
};
