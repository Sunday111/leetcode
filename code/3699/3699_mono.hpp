#include <cstdint>
#include <numeric>


class Solution
{
public:
    using u32 = uint32_t;
    inline static constexpr u32 kMOD = 1'000'000'007;
    inline static u32 dp[2000];

    static u32 zigZagArrays(const u32 n, const u32 l, const u32 r) noexcept
    {
        const u32 m = r - l + 1, m1 = m - 1, k = m / 2;
        [[assume(n > 2)]];
        [[assume(m > 1)]];
        [[assume(m < 2000)]];
        std::iota(dp, dp + m, 0u);

        for (u32 i = 2; i != n; ++i)
        {
            u32 s{};
            for (u32 j = 0; j != k; ++j)
            {
                u32 x = std::exchange(dp[j], s);
                x = std::exchange(dp[m1 - j], x);
                s += x;
                s -= kMOD & -u32{s >= kMOD};
            }
            for (u32 j = k; j != m; ++j)
            {
                u32 x = std::exchange(dp[j], s);
                s += x;
                s -= kMOD & -u32{s >= kMOD};
            }
        }

        return (std::accumulate(dp, dp + m, 0ul) * 2) % kMOD;
    }
};

#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif
