#include <algorithm>
#include <vector>

#include "int_if.hpp"

class Solution
{
public:
    [[nodiscard]] static int intersectionSizeTwo(
        std::vector<std::vector<int>>& intervals) noexcept
    {
        std::ranges::sort(
            intervals,
            [](auto& a, auto& b)
            {
                int la = a[0], ra = a[1], lb = b[0], rb = b[1];
                return iif<int>(ra == rb, la > lb, ra < rb);
            });

        int a = -2, b = -2, c = 0;
        for (auto& interval : intervals)
        {
            if (int l = interval[0], r = interval[1]; a < l)
            {
                int t = l > b;
                c += 1 + t;
                a = iif(t, r - 1, b);
                b = r;
            }
        }

        return c;
    }
};
