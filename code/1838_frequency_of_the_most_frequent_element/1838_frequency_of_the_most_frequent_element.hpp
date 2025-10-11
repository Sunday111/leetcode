#include <algorithm>
#include <span>
#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 maxFrequency(
        std::vector<int>& _nums,
        u32 k) noexcept
    {
        const std::span<u32> nums = reinterpret_range<u32>(_nums);
        radix_sort<10, 2, SortOrder::Descending>(nums);

        auto i = nums.begin(), j = i, e = nums.end();
        u32 r = 0;
        while (j != e && std::distance(i, e) > r)
        {
            if (u32 d = *i - *j; d <= k)
            {
                r = std::max(r, static_cast<u32>(++j - i));
                k -= d;
            }
            else
            {
                u32 pv = *i++;
                k += (j - i) * (pv - *i);
            }
        }

        return r;
    }
};
