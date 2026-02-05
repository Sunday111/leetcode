#include <ranges>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr auto constructTransformedArray(
        const std::vector<int>& nums) noexcept
    {
        const int n = static_cast<int>(nums.size());
        return std::ranges::to<std::vector>(
            std::views::iota(0, n) |
            std::views::transform(
                [&, t = 100 * n](int i)
                {
                    return nums[static_cast<u32>(
                        (i + nums[static_cast<u32>(i)] + t) % n)];
                }));
    }
};
