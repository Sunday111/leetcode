#include <algorithm>
#include <span>

class Solution
{
public:
    [[nodiscard]] static constexpr int maxSubArray(
        std::span<const int> nums) noexcept
    {
        int min_sum = 0, sum = 0, r = nums.front();
        for (int x : nums)
        {
            sum += x;
            r = std::max(r, sum - min_sum);
            min_sum = std::min(min_sum, sum);
        }

        return r;
    }
};
