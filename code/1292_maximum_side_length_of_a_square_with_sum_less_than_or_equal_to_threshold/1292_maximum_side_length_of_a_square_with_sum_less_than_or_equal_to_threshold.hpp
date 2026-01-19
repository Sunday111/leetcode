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
        const u32 h1 = static_cast<u32>(mat.size() + 1),
                  w1 = static_cast<u32>(mat[0].size() + 1);

        for (u32 y = 1; y != h1; ++y)
        {
            for (u32 x = 1; x != w1; ++x)
            {
                u32 v = static_cast<u32>(mat[y - 1][x - 1]);
                p[y][x] = v + p[y - 1][x] + p[y][x - 1] - p[y - 1][x - 1];
            }
        }

        u32 side = 1;
        for (u32 y = 1; y != h1; y = std::max(y + 1, side))
        {
            for (u32 x = side; x != w1 && y >= side; ++x)
            {
                u32 y1 = y - side;
                u32 x1 = x - side;
                u32 sum = p[y][x] - p[y1][x] - p[y][x1] + p[y1][x1];
                side += sum <= threshold;
            }
        }

        return side - 1;
    }
};
