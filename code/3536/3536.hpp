#include <algorithm>

class Solution
{
public:
    int maxProduct(int n)
    {
        int f[10]{};
        while (n)
        {
            ++f[n % 10];
            n /= 10;
        }
        int r = 1, t = 0;
        for (int d = 9; d != 0 && t < 2; --d)
        {
            int x = f[d];
            r *= std::max(d & -(x > 0 && t < 2), 1);
            t += x > 0;
            r *= std::max(d & -(x > 1 && t < 2), 1);
            t += x > 1;
        }
        return r & -(t >= 2);
    }
};
