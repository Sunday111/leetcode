#include <algorithm>
#include <bit>
#include <concepts>
#include <type_traits>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

template <typename T>
    requires(std::is_pointer_v<T>)
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return std::bit_cast<T>(
        iif(c, std::bit_cast<std::size_t>(a), std::bit_cast<std::size_t>(b)));
}

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T negate_if(bool c, T v) noexcept
{
    return iif(c, -v, v);
}

class Solution
{
public:
    [[nodiscard]] static int intersectionSizeTwo(
        std::vector<std::vector<int>>& intervals) noexcept
    {
        std::ranges::sort(
            intervals,
            [](auto& a, auto& b)
            {
                int la = a[0], ra = a[1], lb = b[0], rb = b[1];
                return iif<int>(ra == rb, la > lb, ra < rb);
            });

        int a = -2, b = -2, c = 0;
        for (auto& interval : intervals)
        {
            if (int l = interval[0], r = interval[1]; a < l)
            {
                int t = l > b;
                c += 1 + t;
                a = iif(t, r - 1, b);
                b = r;
            }
        }

        return c;
    }
};
