#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int largestPerimeter(
        std::vector<int>& nums) noexcept
    {
        radix_sort<u32, SortOrder::Ascending, 10, 2>(
            reinterpret_range<u32>(nums));
        for (size_t n = nums.size(), i = 0; i != n - 2; ++i)
        {
            if (size_t j = i + 1, k = j + 1; nums[i] < nums[j] + nums[k])
            {
                return nums[i] + nums[j] + nums[k];
            }
        }

        return 0;
    }
};
