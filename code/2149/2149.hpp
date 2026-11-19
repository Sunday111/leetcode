#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> rearrangeArray(
        const std::vector<int>& nums) noexcept
    {
        std::vector<int> r;
        r.resize(nums.size());

        size_t p = 0, n = 1;

        for (int v : nums)
        {
            auto& i = v < 0 ? n : p;
            r[i] = v;
            i += 2;
        }

        return r;
    }
};
