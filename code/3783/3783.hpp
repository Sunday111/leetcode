#include <cmath>

class Solution
{
public:
    static int reverse(int x) noexcept
    {
        int r = 0;
        while (x)
        {
            (r *= 10) += (x % 10);
            x /= 10;
        }
        return r;
    }

    static int mirrorDistance(int n) { return std::abs(n - reverse(n)); }
};
