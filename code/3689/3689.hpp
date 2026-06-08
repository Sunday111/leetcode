#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    auto maxTotalValue(const std::vector<int>& nums, u32 k) noexcept
    {
        auto [lo, hi] = std::ranges::minmax(nums);
        return static_cast<u64>(hi - lo) * k;
    }
};
