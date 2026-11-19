#include <bitset>

class Solution
{
public:
    int smallestRepunitDivByK(const unsigned y)
    {
        unsigned p = 1 % y, s = y;
        std::bitset<100'000> seen;
        if ((y % 2) && (y % 5))
        {
            while (((s += p) %= y) && !seen[s])
            {
                seen[s] = 1;
                (p *= 10) %= y;
            }
        }

        return s ? -1 : static_cast<int>(seen.count()) + 1;
    }
};
