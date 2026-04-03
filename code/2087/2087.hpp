#include <vector>

namespace xyz
{
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"

class Solution
{
public:
    int minCost(
        const std::vector<int>& s,
        const std::vector<int>& h,
        const std::vector<int>& rc,
        const std::vector<int>& cc)
    {
        int y = s[0], x = s[1], hy = h[0], hx = h[1], c = 0;
        while (x > hx) c += cc[--x];
        while (x < hx) c += cc[++x];
        while (y > hy) c += rc[--y];
        while (y < hy) c += rc[++y];
        return c;
    }
};

#pragma GCC diagnostic pop
