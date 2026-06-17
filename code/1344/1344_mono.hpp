#include <algorithm>
#include <cstdlib>


class Solution
{
public:
    auto angleClock(int h, int m) noexcept
    {
        int t = std::abs(60 * h - 11 * m);
        return static_cast<float>(std::min(t, 720 - t)) / 2.f;
    }
};
