#pragma once

#include <unordered_map>
#include <vector>

class Solution
{
public:
    int subarraySum(const std::vector<int>& nums, int k)
    {
        int sum = 0, count = 0;

        std::unordered_map<int, int> sum_to_frequency;

        // In the worst case (all ones) we will have n different sums
        // reserve twice of that to reduce the chance of collisions
        sum_to_frequency.reserve(2 * nums.size());

        for (int v : nums)
        {
            sum_to_frequency[sum]++;
            sum += v;

            // if there previously was a cumulative sum which is less than
            // the current one by k it is safe to conclude there is a subarray
            // with the sum of that ends at this index
            if (auto it = sum_to_frequency.find(sum - k);
                it != sum_to_frequency.end())
            {
                count += it->second;
            }
        }

        return count;
    }
};
