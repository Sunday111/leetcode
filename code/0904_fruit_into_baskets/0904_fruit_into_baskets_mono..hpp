#include <concepts>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define HOT_PATH __attribute__((hot))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T branchless_max(
    T a,
    T b) noexcept
{
    T m = static_cast<T>(-T{a > b});
    return (m & a) | (~m & b);
}

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

class Solution
{
public:
    [[nodiscard]] static constexpr int totalFruit(
        const std::vector<int>& fruits) noexcept
    {
        int r = 0;
        int f1 = -1, f2 = -1;
        int l = 0;
        int n1 = 0, n2 = 0;
        for (int f : fruits)
        {
            int p = n1;
            bool c1 = f == f1, c2 = f == f2, c12 = c1 || c2;
            n1 = iif(c1, n2, n1);
            n2 = iif(c1, p, n2);
            f1 = iif(c2, f1, f2);
            f2 = iif(c2, f2, f);
            n1 = iif(c12, n1, l);
            n2 = iif(c12, n2, 0) + 1;
            l = iif(c2, l, 0) + 1;
            r = branchless_max(r, n1 + n2);
        }
        return r;
    }
};
