#pragma once

#include <array>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 maximumUniqueSubarray(
        std::vector<int>& nums) noexcept
    {
        std::array<uint16_t, 10'001> freq{};

        const auto n = static_cast<u32>(nums.size());
        u32 max_sum = 0;
        for (u32 l = 0, r = 0, sum = 0; r != n; ++r)
        {
            auto rv = static_cast<u32>(nums[r]);
            sum += rv;
            auto& cnt = ++freq[rv];
            while (cnt > 1)
            {
                auto lv = static_cast<u32>(nums[l++]);
                sum -= lv;
                --freq[lv];
            }
            max_sum = std::max(max_sum, sum);
        }
        return max_sum;
    }
};
