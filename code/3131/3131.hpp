#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] constexpr int addedInteger(
        const std::vector<int>& nums1,
        const std::vector<int>& nums2) const noexcept
    {
        return std::ranges::max(nums2) - std::ranges::max(nums1);
    }
};
