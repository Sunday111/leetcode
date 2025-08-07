#include <concepts>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

class Solution
{
public:
    int maxCollectedFruits(std::vector<std::vector<int>>& fruits)
    {
        using u16 = uint16_t;
        auto n = static_cast<u16>(fruits.size());

        for (u16 i = n; --i;)
        {
            fruits[i - 1][i - 1] += std::exchange(fruits[i][i], 0);
        }

        for (u16 x = n - 1; x--;)
        {
            u16 rx = x + 1;
            for (u16 y = x + 1; y != n; ++y)
            {
                int mv = fruits[y][rx];

                if (u16 ry = y - 1; rx < ry)
                {
                    mv = std::max(mv, fruits[ry][rx]);
                }

                if (u16 ry = y + 1; ry != n)
                {
                    mv = std::max(mv, fruits[ry][rx]);
                }

                fruits[y][x] += mv;
            }
        }

        for (u16 y = n - 1; y--;)
        {
            u16 ry = y + 1;
            for (u16 x = y + 1; x != n; ++x)
            {
                int a = fruits[ry][x];
                u16 rx1 = x - 1;
                int b = iif<int>(rx1 > ry, fruits[ry][rx1], 0);
                u16 rx2 = x + 1;
                int c = iif<int>(rx2 > ry, fruits[ry][rx2], 0);
                fruits[y][x] += std::max({a, b, c});
            }
        }

        return fruits[0][0] + fruits[n - 1][0] + +fruits[0][n - 1];
    }
};
