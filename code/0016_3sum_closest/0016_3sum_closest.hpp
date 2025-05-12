#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

class Solution
{
public:
    int threeSumClosest(std::vector<int32_t>& nums, const int target)
    {
        std::ranges::sort(nums);

        int closest = nums[0] + nums[1] + nums[2];
        int min_diff = std::abs(target - closest);

        const auto end = nums.end();
        const auto iend = std::next(end, -2);
        const auto kbegin = std::next(end, -1);
        for (auto i = nums.begin(); i != iend;
             i = std::upper_bound(i, iend, *i))
        {
            const int iv = *i;

            auto j = std::next(i);
            auto k = kbegin;

            // Check if range of possible sums intersects
            // with range [t - min_diff; t + min_diff]
            if ((iv + 2 * *j > target + min_diff) ||
                (*k + *iend + iv + min_diff < target))
            {
                break;
            }

            while (j < k)
            {
                int s = iv + *j + *k;
                if (auto diff = std::abs(target - s); diff < min_diff)
                {
                    closest = s;
                    min_diff = diff;
                    if (diff == 0) return closest;
                }

                if (s < target)
                {
                    ++j;
                }
                else
                {
                    --k;
                }
            }
        }

        return closest;
    }
};
