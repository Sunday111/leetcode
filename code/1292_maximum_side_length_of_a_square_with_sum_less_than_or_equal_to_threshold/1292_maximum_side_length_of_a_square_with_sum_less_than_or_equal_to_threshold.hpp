#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static u32 maxSideLength(
        const std::vector<std::vector<int>>& mat,
        u32 threshold) noexcept
    {
        static u32 p[302][302];
        const u32 h = static_cast<u32>(mat.size()),
                  w = static_cast<u32>(mat[0].size());

        for (u32 y = 1, h1 = h + 1; y != h1; ++y)
        {
            for (u32 x = 1, w1 = w + 1; x != w1; ++x)
            {
                u32 v = static_cast<u32>(mat[y - 1][x - 1]);
                p[y][x] = v + p[y - 1][x] + p[y][x - 1] - p[y - 1][x - 1];
            }
        }

        u32 max_side = 0;
        for (u32 y = 0, max_h = h; y != h && max_h > max_side; ++y, --max_h)
        {
            for (u32 x = 0, max_w = w; x != w && max_w > max_side; ++x, --max_w)
            {
                u32 lim_t = std::min(max_w, max_h) + 1, a = p[y][x];
                for (u32 t = std::min(max_side + 1, lim_t); t != lim_t; ++t)
                {
                    u32 b = p[y][x + t];
                    u32 c = p[y + t][x];
                    u32 d = p[y + t][x + t];
                    u32 s = d + a - (b + c);

                    if (s > threshold) break;
                    max_side = std::max(max_side, t);
                }
            }
        }

        return max_side;
    }
};
