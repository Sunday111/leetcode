#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int minTimeToVisitAllPoints(
        const std::vector<std::vector<int>>& points) noexcept
    {
        int r = 0, px = points[0][0], py = points[0][1];
        for (size_t n = points.size(), i = 1; i != n; ++i)
        {
            auto& p = points[i];
            int x = p[0], y = p[1];
            r += std::max(
                std::abs(std::exchange(px, x) - x),
                std::abs(std::exchange(py, y) - y));
        }
        return r;
    }
};
