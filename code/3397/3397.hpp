#include "int_if.hpp"
#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static int maxDistinctElements(
        std::vector<int>& nums,
        int k) noexcept
    {
        radix_sort<8, 4, SortOrder::Ascending>(std::span{nums});
        int t = nums.back() + k + 1, r = 0;
        int stop = nums.front() - k;
        for (u32 i = static_cast<u32>(nums.size()); i-- && t > stop;)
        {
            int v = nums[i];
            int h = std::min(v + k, t - 1);
            int b = v - k <= h;
            r += b;
            t = iif(b, h, t);
        }
        return r;
    }
};

#include "sync_stdio.hpp"
