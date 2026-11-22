#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int addedInteger(
        const std::vector<int>& nums1,
        const std::vector<int>& nums2) noexcept
    {
        return std::ranges::max(nums2) - std::ranges::max(nums1);
    }
};
