#pragma once

#include <algorithm>
#include <span>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> pivotArray(
        const std::vector<int>& nums,
        int pivot) noexcept
    {
        std::vector<int> r;
        r.resize(nums.size());

        size_t i = 0, j = nums.size();
        for (int v : nums)
        {
            if (v < pivot)
            {
                r[i++] = v;
            }
            else if (v > pivot)
            {
                r[--j] = v;
            }
        }

        std::ranges::reverse(std::span{r}.subspan(j));
        std::ranges::fill(std::span{r}.subspan(i, j - i), pivot);

        return r;
    }
};
