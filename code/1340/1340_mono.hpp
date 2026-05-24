#include <algorithm>
#include <cstdint>
#include <functional>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;




inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::max(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_max =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, max2);

class Solution
{
public:
    [[nodiscard]] u16 maxJumps(std::vector<int>& a, u16 d) noexcept
    {
        constexpr u16 max_n = 1000;
        const u16 n = a.size() & 0xFFFF;
        [[assume(n <= max_n)]];

        static u16 srt[max_n], dp[max_n];
        std::iota(srt, srt + n, 0);
        std::ranges::sort(
            srt,
            srt + n,
            std::greater{},
            [&](u16 i) { return a[i]; });
        std::fill_n(dp, n, 1);

        for (u16 i : srt | std::views::take(n))
        {
            [[assume(i < n)]];

            u16 jumps = dp[i] + 1;
            int v = a[i];

            u16 l = i - std::min(i, d);
            for (u16 j = i; j-- != l && a[j] < v;)
            {
                upd_max(dp[j], jumps);
            }

            u16 r = std::min<u16>(i + d + 1, n);
            for (u16 j = i + 1; j != r && a[j] < v; ++j)
            {
                upd_max(dp[j], jumps);
            }
        }

        return std::ranges::max(dp | std::views::take(n));
    }
};
