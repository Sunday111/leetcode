#include <vector>

#include "radix_sort/radix_sort.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int largestPerimeter(
        std::vector<int>& nums) noexcept
    {
        radix_sort<20>(
            reinterpret_cast<u32*>(nums.data()),
            static_cast<u32>(nums.size()));
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
