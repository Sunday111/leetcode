#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] constexpr static int maxSub(std::vector<int>& arr) noexcept
    {
        std::ranges::sort(arr);

        int r = 1;
        for (int x = 0, p = -1; int v : arr)
        {
            x &= -(v == p);
            p = v + 1;
            r = std::max(++x, r);
        }

        return r;
    }

    [[nodiscard]] constexpr static int maximizeSquareHoleArea(
        int,
        int,
        std::vector<int>& hBars,
        std::vector<int>& vBars) noexcept
    {
        int w = std::min(maxSub(hBars), maxSub(vBars)) + 1;
        return w * w;
    }
};
