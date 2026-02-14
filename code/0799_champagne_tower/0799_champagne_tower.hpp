#include <algorithm>

class Solution
{
public:
    [[nodiscard]] double
    champagneTower(double poured, unsigned qrow, unsigned qcol) noexcept
    {
        double a[2][101];
        double *curr = a[0], *next = a[1];
        curr[0] = poured;

        for (auto y = 0u; y != qrow; ++y)
        {
            next[0] = 0;
            for (auto x = 0u; x != y + 1; ++x)
            {
                auto spread = std::max((curr[x] - 1) / 2, 0.0);
                next[x] += spread;
                next[x + 1] = spread;
            }

            std::swap(curr, next);
        }

        return std::min(1.0, curr[qcol]);
    }
};
