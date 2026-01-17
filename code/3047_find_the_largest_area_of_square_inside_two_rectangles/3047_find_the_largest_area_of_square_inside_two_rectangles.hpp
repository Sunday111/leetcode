#include <vector>

#include "force_inline.hpp"

// Intersection between two intervals described as [x1, x2] and [x3, x4]
template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr int
interval_intersection(T x1, T x2, T x3, T x4) noexcept
{
    return std::max(0, std::min(x2, x4) - std::max(x1, x3));
}

class Solution
{
public:
    auto largestSquareArea(
        const std::vector<std::vector<int>>& bottomLeft,
        const std::vector<std::vector<int>>& topRight)
    {
        size_t n = bottomLeft.size();

        int ans = 0;
        for (size_t i = 0; i != n; ++i)
        {
            int x1 = bottomLeft[i][0], y1 = bottomLeft[i][1];
            int x2 = topRight[i][0], y2 = topRight[i][1];
            for (size_t j = i + 1; j != n; ++j)
            {
                int x3 = bottomLeft[j][0], y3 = bottomLeft[j][1];
                int x4 = topRight[j][0], y4 = topRight[j][1];
                int a = interval_intersection(x1, x2, x3, x4);
                int b = interval_intersection(y1, y2, y3, y4);
                ans = std::max(ans, std::min(a, b));
            }
        }

        return 1L * ans * ans;
    }
};
