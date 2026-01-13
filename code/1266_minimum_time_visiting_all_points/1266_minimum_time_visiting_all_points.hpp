#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int minTimeToVisitAllPoints(
        const std::vector<std::vector<int>>& p) noexcept
    {
        int r = 0, px = p[0][0], py = p[0][1];
        for (size_t n = p.size(), i = 1; i != n; ++i)
        {
            const int x = p[i][0], y = p[i][1];
            r += std::max(
                std::abs(std::exchange(px, x) - x),
                std::abs(std::exchange(py, y) - y));
        }
        return r;
    }
};
