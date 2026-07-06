#include <algorithm>
#include <vector>

class Solution
{
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& a) noexcept
    {
        std::ranges::sort(
            a,
            std::less{},
            [&](auto& x) { return std::tuple{x[0], -x[1]}; });

        int r = 0;
        for (int p = 0; auto& x : a)
        {
            int e = x[1];
            r += e > p;
            p = std::max(p, e);
        }

        return r;
    }
};
