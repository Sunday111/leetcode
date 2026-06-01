#include <algorithm>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    u32 minimumCost(std::vector<int>& cost)
    {
        std::ranges::sort(cost);
        u32 n = cast<u32>(cost.size()), k = n % 3, s = 0;
        auto c = reinterpret_cast<const u32*>(cost.data());
        for (u32 i = n; i != k; --i)
        {
            s += c[--i];
            s += c[--i];
        }
        for (u32 i = k; i--;)
        {
            s += c[i];
        }
        return s;
    }
};
