#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    u32 maxSideLength(std::vector<std::vector<int>>& mat, u32 threshold)
    {
        static u32 prefix[302][302];
        u32 h = static_cast<u32>(mat.size()),
            w = static_cast<u32>(mat[0].size());
        u32 h1 = h + 1, w1 = w + 1;

        // Horizontal prefix sum
        for (u32 y = 1; y != h1; ++y)
        {
            prefix[y][0] = 0;
            for (u32 x = 1; x != w1; ++x)
            {
                u32 v = static_cast<u32>(mat[y - 1][x - 1]);
                prefix[y][x] = prefix[y][x - 1] + v;
            }
        }

        // Vertical prefix sum
        for (u32 y = 2; y != h1; ++y)
        {
            for (u32 x = 1; x != w1; ++x)
            {
                prefix[y][x] += prefix[y - 1][x];
            }
        }

        u32 r = 0;
        for (u32 y1 = 1; y1 != h1; ++y1)
        {
            u32 y = y1 - 1;
            auto max_yt = h1 - y1;
            for (u32 x1 = 1; x1 != w1; ++x1)
            {
                u32 x = x1 - 1;
                auto max_xt = w1 - x1;
                auto lim_t = std::min(max_yt, max_xt) + 1;
                u32 a = prefix[y1 - 1][x1 - 1];
                for (u32 t = 1, yt = y + 1, xt = x + 1; t != lim_t;
                     ++t, ++xt, ++yt)
                {
                    u32 b = prefix[y][xt];
                    u32 c = prefix[yt][x];
                    u32 d = prefix[yt][xt];
                    u32 s = d + a - (b + c);

                    if (s > threshold) break;
                    r = std::max(r, t);
                }
            }
        }

        return r;
    }
};
