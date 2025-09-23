
#include <algorithm>
#include <span>
#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 maxFrequency(
        std::vector<int>& _nums,
        const u32 k) noexcept
    {
        const std::span<u32> nums{
            reinterpret_cast<u32*>(_nums.data()),  // NOLINT
            _nums.size(),
        };
        radix_sort<u32, SortOrder::Descending, 7, 3>(nums);

        auto i = nums.begin(), j = i, e = nums.end();
        u32 count = 0, available_ops = k, r = 0;
        while (true)
        {
            if (j != e && *i - *j <= available_ops)
            {
                u32 delta = *i - *j;
                available_ops -= delta;
                r = std::max(r, ++count);
                ++j;
            }
            else
            {
                u32 pv = *i++;
                if (i == e) break;
                available_ops += --count * (pv - *i);
            }
        }

        return r;
    }
};
