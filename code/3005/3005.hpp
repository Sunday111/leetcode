#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    static constexpr int maxFrequencyElements(
        const std::vector<int>& nums) noexcept
    {
        std::array<int, 101> freq{};
        for (int num : nums) freq[num & 0xFF]++;
        int max_freq = *std::ranges::max_element(freq);
        return max_freq * static_cast<int>(std::ranges::count(freq, max_freq));
    }
};
