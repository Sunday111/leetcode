#include <numeric>
#include <string>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    u32 regionsBySlashes(std::vector<std::string>& g)
    {
        const u32 n = cast<u32>(g.size()), n4 = n * 4;

        static u32 p[30 * 30 * 4];
        std::iota(p, p + n * n * 4, 0);

        auto find = [] [[gnu::always_inline]] (u32 x) -> u32
        {
            while (p[x] != x)
            {
                u32& y = p[x];
                x = y = p[y];
            }
            return x;
        };

        u32 r = 4 * n * n;

        auto merge = [&find, &r] [[gnu::always_inline]] (u32 x, u32 y)
        {
            x = find(x);
            y = find(y);
            p[y] = x;
            r -= x != y;
        };

        constexpr u8 left = 0, right = 1, top = 2, bot = 3;

        for (u32 gy = 0, row_offset = 0; gy != n; ++gy, row_offset += n4)
        {
            for (u32 gx = 0; gx != n; ++gx)
            {
                char c = g[gy][gx];

                u32* t = p + row_offset + gx * 4;

                // connect left and right
                if (c == ' ') merge(t[left], t[right]);

                // connect cells in top right and bottom left corners
                if (c != '/')
                {
                    merge(t[top], t[right]);
                    merge(t[bot], t[left]);
                }

                // connect cells in top left and bottom right corners
                if (c != '\\')
                {
                    merge(t[top], t[left]);
                    merge(t[bot], t[right]);
                }

                // connect with the top cluster
                if (gy != 0) merge(t[top], (t - n4)[bot]);

                // connect with the left cluster
                if (gx != 0) merge(t[left], (t - 4)[right]);
            }
        }

        return r;
    }
};
