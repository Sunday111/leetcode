#include <algorithm>
#include <cstdint>
#include <functional>
#include <ranges>
#include <string>
#include <utility>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;




inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::min(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);

class Solution
{
public:
    inline static u32 dist[26][26];

    inline static auto _init_ = []
    {
        for (u8 i = 0; i != 26; ++i)
        {
            u8 ix = i % 6, iy = i / 6;
            for (u8 j = 0; j != 26; ++j)
            {
                u8 jx = j % 6, jy = j / 6;
                dist[i][j] = (std::max(ix, jx) - std::min(ix, jx)) +
                             (std::max(iy, jy) - std::min(iy, jy));
            }
        }
        return 'a';
    }();

    u32 minimumDistance(std::string& word) const noexcept
    {
        u32 dp[2][26][26]{};

        bool f = false;

        u8 j = (word[0] - 'A') & 0xFF;

        for (char c : word | std::views::drop(1))
        {
            const u8 k = (c - 'A') & 0xFF;
            u32 dj = dist[j][k];

            f = !f;

            for (u8 i = 0; i != 26; ++i)
            {
                for (u8 jj = 0; jj != 26; ++jj)
                {
                    dp[f][i][jj] = 100'000;
                }
            }

            for (u8 i = 0; i != 26; ++i)
            {
                u32 di = dist[k][i];

                upd_min(dp[f][k][j], dp[!f][i][j] + di);
                upd_min(dp[f][k][i], dp[!f][j][i] + dj);
                upd_min(dp[f][i][k], dp[!f][i][j] + dj);
                upd_min(dp[f][j][k], dp[!f][j][i] + di);
            }
            j = k;
        }

        u32 r = 100'000;

        u8 k = (*(word.rbegin()) - 'A') & 0xFF;
        j = (*(word.rbegin() + 1) - 'A') & 0xFF;

        for (u8 i = 0; i != 26; ++i)
        {
            upd_min(r, dp[f][k][j]);
            upd_min(r, dp[f][k][i]);
            upd_min(r, dp[f][i][k]);
            upd_min(r, dp[f][j][k]);
        }

        return r;
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
