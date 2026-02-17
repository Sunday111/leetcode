#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] static u32 firstUniqueFreq(
        const std::vector<u32>& nums) noexcept
    {
        static u32 freq_freq[100'001], num_freq[100'001];

        u32 min_v = nums[0], max_v = min_v;

        for (u32 v : nums)
        {
            num_freq[v]++;
            min_v = std::min(min_v, v);
            max_v = std::max(max_v, v);
        }

        u32 min_f = 100'000, max_f = 0;
        for (u32 v = min_v; v <= max_v; ++v)
        {
            u32 f = num_freq[v];
            freq_freq[f]++;
            min_f = std::min(min_f, f);
            max_f = std::max(max_f, f);
        }

        u32 r = ~u32{};
        for (u32 v : nums)
        {
            if (freq_freq[num_freq[v]] == 1)
            {
                r = v;
                break;
            }
        }

        std::fill(num_freq + min_v, num_freq + max_v + 1, 0u);
        std::fill(freq_freq + min_f, freq_freq + max_f + 1, 0u);

        return r;
    }

    [[nodiscard]] static auto firstUniqueFreq(
        const std::vector<i32>& nums) noexcept
    {
        return std::bit_cast<i32>(
            firstUniqueFreq(reinterpret_cast<const std::vector<u32>&>(nums)));
    }
};
