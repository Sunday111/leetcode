#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    int longestBalanced(std::vector<int>& nums)
    {
        static u64 seen[(100'001 / 64) + 1];
        u16 n = nums.size() & 0xFFFF, r = 0;
        for (u16 i = 0; n - i > r; ++i)
        {
            u16 mw = 0, e = 0, o = 0;
            for (u16 j = i, l = 1; j != n && n - i > r; ++j, ++l)
            {
                u32 v = static_cast<u32>(nums[j]);
                u16 wi = (v >> 6) & 0xFFFF;
                u64 mask = u64{1} << (v & 63);
                u64& w = seen[wi];
                bool is_odd = v & 1;
                bool is_new = !(w & mask);
                e += !is_odd & is_new;
                o += is_odd & is_new;
                w |= mask;
                r = std::max<u16>(r, -(e == o) & l);
                mw = std::max(mw, wi);
            }
            std::fill_n(seen, mw + 1, 0);
        }

        return r;
    }
};
