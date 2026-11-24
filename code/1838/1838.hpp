#include <algorithm>
#include <vector>

#include "radix_sort/radix_sort.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 maxFrequency(
        std::vector<int>& _nums,
        u32 k) noexcept
    {
        auto* nums = reinterpret_cast<u32*>(_nums.data());
        const auto n = static_cast<u32>(_nums.size());
        radix_sort<20, 10, SortOrder::Descending>(nums, n);

        auto i = nums, j = i, e = nums + n;
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
