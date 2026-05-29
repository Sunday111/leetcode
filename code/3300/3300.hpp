#include <vector>

#include "cast_view.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    u32 minElement(std::vector<int>& nums)
    {
        u32 r = 9 * 4;

        for (u32 x : nums | cast_view<u32>)
        {
            u32 s = x % 10 + (x / 10) % 10 + (x / 100) % 10 + (x / 1000) % 10;
            r = std::min(r, s);
        }

        return std::max(r, 1u);
    }
};
