#include <algorithm>
#include <vector>

#include "swap_if_greater.hpp"
#include "swap_if_lower.hpp"

class Solution
{
public:
    int maximumProduct(const std::vector<int>& nums) noexcept
    {
        int hi[3]{-1000, -1000, -1000}, lo[2]{1000, 1000};

        for (int x : nums)
        {
            hi[0] = std::max(x, hi[0]);
            lo[1] = std::min(lo[1], x);
            swap_if_greater(hi[0], hi[1]);
            swap_if_greater(hi[1], hi[2]);
            swap_if_lower(lo[1], lo[0]);
        }

        return std::max(hi[0] * hi[1] * hi[2], hi[2] * lo[0] * lo[1]);
    }
};
