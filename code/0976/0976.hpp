#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int largestPerimeter(
        std::vector<int>& nums) noexcept
    {
        std::ranges::sort(nums, std::greater{});
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
