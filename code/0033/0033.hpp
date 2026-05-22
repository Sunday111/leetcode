#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    int search(std::vector<int>& a, int x)
    {
        u32 l = 0, r = static_cast<u32>(a.size() - 1);

        while (l <= r)
        {
            u32 m = (l + r) / 2;

            if (a[m] == x) return static_cast<int>(m);

            if (a[m] >= a[l] ? !(x >= a[l] && x < a[m])
                             : (x > a[m] && x <= a[r]))
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        return -1;
    }
};
