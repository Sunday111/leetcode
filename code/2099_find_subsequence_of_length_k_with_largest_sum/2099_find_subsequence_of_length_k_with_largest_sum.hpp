#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr std::vector<int> maxSubsequence(
        std::vector<int> nums,
        u16 k) noexcept
    {
        auto proj = [&](int i)
        {
            return nums[static_cast<u16>(i)];
        };

        std::vector<int> indices;
        indices.reserve(nums.size());
        const int n = static_cast<int>(nums.size());
        for (int i = 0; i != n; ++i) indices.push_back(i);
        std::ranges::sort(indices, std::greater{}, proj);
        indices.resize(k);
        std::ranges::sort(indices, std::less{});
        for (int& i : indices)
        {
            int v = nums[static_cast<u16>(i)];
            i = v;
        };
        return indices;
    }
};
