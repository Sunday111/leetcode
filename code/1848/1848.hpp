#include <vector>

#include "int_if.hpp"
#include "upd_min.hpp"

class Solution
{
public:
    using u32 = uint32_t;
    u32 getMinDistance(std::vector<int>& nums, int target, u32 start)
    {
        u32 n = cast<u32>(nums.size()), r = n;
        for (u32 i = 0; i != n; ++i)
        {
            upd_min(
                r,
                iif(nums[i] == target,
                    (std::max(i, start) - std::min(i, start)),
                    n));
        }
        return r;
    }
};
