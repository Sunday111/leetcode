#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr i64 pass(
        const std::vector<int>& nums,
        i32 max) noexcept NO_SANITIZERS HOT_PATH
    {
        i64 count = 0;
        auto l = nums.begin(), r = nums.end() - 1;
        while (l != r)
        {
            auto ok = *l + *r <= max;
            count += ok * (r - l);
            l += ok;
            r -= !ok;
        }
        return count;
    }

    [[nodiscard]] static constexpr i64
    countFairPairs(std::vector<i32>& nums, i32 lower, i32 upper) noexcept
    {
        radix_sort<i32, SortOrder::Ascending, 16, 2>(nums);

        return pass(nums, upper) - pass(nums, lower - 1);
    }
};
