#include <algorithm>
#include <ranges>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr bool isNegative(int v) noexcept
    {
        return v < 0;
    }

    [[nodiscard]] static constexpr auto countNegatives(
        const std::vector<std::vector<int>>& grid) noexcept
    {
        return std::ranges::count_if(std::views::join(grid), isNegative);
    }
};
