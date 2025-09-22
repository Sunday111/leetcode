#pragma once

#include <algorithm>
#include <span>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    inline static std::array<u32, 200'005> freq;
    inline static std::array<u32, 200'005> prefixSum;

    [[nodiscard]] static constexpr u32 maxFrequency(
        std::vector<int>& _nums,
        const u32 k,
        const u32 operations) noexcept
    {
        const std::span<u32> nums{
            reinterpret_cast<u32*>(_nums.data()),  // NOLINT
            _nums.size(),
        };

        u32 maxVal = *std::ranges::max_element(nums);
        u32 n = maxVal + k + 2;
        std::ranges::fill_n(freq.begin(), n, u32{});
        for (auto num : nums) ++freq[num];

        if (auto it = freq.begin(); operations == 0)
        {
            return *std::max_element(it, std::next(it, n));
        }

        prefixSum[n] = 0;
        prefixSum[0] = freq[0];
        for (u32 i = 1; i != n; ++i) prefixSum[i] = prefixSum[i - 1] + freq[i];

        u32 maxFreq = 0;
        for (u32 target = 0; target <= maxVal; ++target)
        {
            u32 left = target > k ? target - k : n + 1;
            u32 right = std::min(n - 1, target + k);
            u32 totalCount = prefixSum[right] - prefixSum[left - 1];
            u32 canChange = totalCount - freq[target];
            u32 possibleFreq = freq[target] + std::min(operations, canChange);
            maxFreq = std::max(maxFreq, possibleFreq);
        }

        return maxFreq;
    }
};
