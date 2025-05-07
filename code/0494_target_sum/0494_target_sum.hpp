#pragma once

#include <numeric>
#include <vector>

// Let the total sum of all values in the array be S, and suppose we split the
// numbers into two groups: P (with + signs) and N (with - signs). Then:
//
// P + N = S                  // The total sum remains the same
// P - N = T                  // The signed sum must equal the target T
//
// Solving these equations:
// From the first:   N = S - P         (1)
// Plug into the second: P - (S - P) = T
// Simplifies to:    2P - S = T
// So:               P = (S + T) / 2
//
// Therefore, the problem reduces to counting how many subsets of the array
// sum up to the value P = (S + T) / 2.
class Solution
{
public:
    int32_t findTargetSumWays(std::vector<int32_t>& nums, int32_t t)
    {
        const auto s = std::reduce(nums.begin(), nums.end());
        const auto p = (t + s) / 2;
        if (s < std::abs(t) || ((t + s) % 2) != 0) return 0;

        std::vector<int32_t> count(std::bit_cast<unsigned>(p + 1), 0);
        count[0] = 1;

        for (auto v : nums)
        {
            for (int32_t i = p; i >= v; --i)
            {
                count[std::bit_cast<uint32_t>(i)] +=
                    count[std::bit_cast<uint32_t>(i - v)];
            }
        }

        return count.back();
    }
};
