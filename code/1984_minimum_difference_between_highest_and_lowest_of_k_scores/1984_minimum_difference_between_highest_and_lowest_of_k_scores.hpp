#include <algorithm>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 minimumDifference(
        std::vector<int>& nums,
        u32 k) noexcept
    {
        std::ranges::sort(nums);
        u32 ans = std::numeric_limits<int>::max();
        for (u32 i = 0; i != nums.size() - (k - 1); ++i)
        {
            ans = std::min(ans, static_cast<u32>(nums[i + (k - 1)] - nums[i]));
        }
        return ans;
    }
};
