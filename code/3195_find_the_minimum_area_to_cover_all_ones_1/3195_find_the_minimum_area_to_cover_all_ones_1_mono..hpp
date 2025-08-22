#include <concepts>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define HOT_PATH __attribute__((hot))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T int_min(T a, T b) noexcept
{
    return iif(a < b, a, b);
}

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T int_max(T a, T b) noexcept
{
    return iif(a > b, a, b);
}

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr int minimumArea(
        const std::vector<std::vector<int>>& grid) noexcept
    {
        const u16 h = grid.size() & 0xFFFF, w = grid.front().size() & 0xFFFF;
        u16 min_x = w, min_y = h, max_x = 0, max_y = 0;
        for (u16 y = 0; y != h; ++y)
        {
            auto& r = grid[y];
            bool has_some = false;
            for (u16 x = 0; x != w; ++x)
            {
                has_some |= r[x];
                min_x = iif(r[x], int_min(min_x, x), min_x);
                max_x = iif(r[x], int_max(max_x, x), max_x);
            }

            min_y = iif(has_some, int_min(min_y, y), min_y);
            max_y = iif(has_some, y, max_y);
        }

        return static_cast<int>((max_x - min_x) + 1) *
               static_cast<int>((max_y - min_y) + 1);
    }
};
