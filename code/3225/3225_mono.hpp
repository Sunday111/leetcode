#include <algorithm>
#include <cstdint>
#include <functional>
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
    [[nodiscard]] u64 maximumScore(
        const std::vector<std::vector<int>>& g) const noexcept
    {
        return impl(reinterpret_cast<const std::vector<std::vector<u32>>&>(g));
    }

    [[nodiscard]] static u64 impl(
        const std::vector<std::vector<u32>>& g) noexcept
    {
        const u32 n = static_cast<u32>(g.size()), n1 = n + 1;
        static u64 s[2][101], dp[2][101][2];
        memset(dp[0], 0, 16 * n1);
        s[0][0] = s[1][0] = 0;
        for (u32 i = 0; i != n; i++)
        {
            s[0][i + 1] = s[0][i] + g[i][0];
        }

        u32 prev = 0, curr = 1;
        for (u32 col = 0; col < n - 1; col++)
        {
            for (u32 i = 0; i != n; i++)
            {
                s[curr][i + 1] = s[curr][i] + g[i][col + 1];
            }

            u64 preMax = dp[prev][0][1];
            for (u32 nb = 1; nb != n1; nb++)
            {
                dp[curr][nb][0] = dp[curr][nb][1] =
                    std::max(dp[prev][nb][0], preMax + s[prev][nb]);
                upd_max(
                    preMax,
                    dp[prev][nb][1] - std::min(dp[prev][nb][1], s[prev][nb]));
            }

            u64 sm = dp[prev][n][0] + s[curr][n];
            for (u32 nb = n - 1; nb; nb--)
            {
                upd_max(dp[curr][nb][0], sm - s[curr][nb]);
                sm = std::max(sm, dp[prev][nb][0] + s[curr][nb]);
            }

            dp[curr][0][0] = sm;
            dp[curr][0][1] = std::max(dp[prev][0][0], dp[prev][n][0]);
            std::swap(prev, curr);
        }

        return std::ranges::max(
            dp[prev] | std::views::take(n1) | std::views::join);
    }
};
