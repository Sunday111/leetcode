#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int maxCollectedFruits(
        std::vector<std::vector<int>>& fruits) noexcept
    {
        using u16 = uint16_t;
        auto n = static_cast<u16>(fruits.size());

        for (u16 x = n - 1; x--;)
        {
            u16 rx = x + 1;
            fruits[x][x] += std::exchange(fruits[rx][rx], 0);
            for (u16 y = x + 1; y != n; ++y)
            {
                int a = fruits[y][rx], b = fruits[rx][y];

                if (u16 ry = y - 1; rx < ry)
                {
                    a = std::max(a, fruits[ry][rx]);
                    b = std::max(b, fruits[rx][ry]);
                }

                if (u16 ry = y + 1; ry != n)
                {
                    a = std::max(a, fruits[ry][rx]);
                    b = std::max(b, fruits[rx][ry]);
                }

                fruits[y][x] += a, fruits[x][y] += b;
            }
        }

        return fruits[0][0] + fruits[n - 1][0] + fruits[0][n - 1];
    }
};
