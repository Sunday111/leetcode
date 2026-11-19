#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::vector<int>> divideArray(
        std::vector<int>& nums,
        int k) noexcept
    {
        size_t n = nums.size();
        size_t p = n / 3;
        std::vector<std::vector<int>> r;
        r.resize(p);
        std::ranges::sort(nums);

        auto a = r.begin();
        a->push_back(nums[0]);
        for (size_t i = 1; i != n; ++i)
        {
            int v = nums[i];
            if (a->size() == 3)
            {
                std::advance(a, 1);
                a->reserve(3);
                a->push_back(v);
            }
            else
            {
                if (v - a->front() > k) return {};
                a->push_back(v);
            }
        }

        return r;
    }
};
