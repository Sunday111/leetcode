#include <array>
#include <concepts>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

// Swaps a and b if a > b. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void swap_if_greater(Int& a, Int& b) noexcept
{
    Int mask = (a ^ b) & -Int{a > b};
    a ^= mask, b ^= mask;
}

template <std::integral Int, size_t n>
FORCE_INLINE static constexpr void update_minima(
    Int x,
    std::array<Int, n>& vals) noexcept
{
#pragma GCC unroll
    for (auto& v : vals) swap_if_greater(v, x);
}

class Solution
{
public:
    [[nodiscard]] static constexpr int maxSumDivThree(
        const std::vector<int>& nums) noexcept
    {
        int s = 0;

        int n1{}, n2{};
        constexpr auto mi = std::numeric_limits<int>::max();
        std::array<int, 2> m1{}, m2{};
        m1.fill(mi), m2.fill(mi);

        for (int v : nums)
        {
            s += v;
            int m = v % 3;
            bool b1 = m == 1, b2 = m == 2;
            n1 += v & -b1, n2 += v & -b2;
            update_minima(iif(b1, v, mi), m1);
            update_minima(iif(b2, v, mi), m2);
        }

        int m = s % 3, k = s & -!!m;
        if (n1 > 0 && m == 1) k = std::min(k, m1[0]);
        if (n2 > 1 && m == 1) k = std::min(k, m2[0] + m2[1]);
        if (n1 > 1 && m == 2) k = std::min(k, m1[0] + m1[1]);
        if (n2 > 0 && m == 2) k = std::min(k, m2[0]);
        return s - k;
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
