#include <algorithm>
#include <concepts>
#include <cstdint>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>



using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;



template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};



inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};

class Solution
{
public:
    u32 maxDistance(
        const u32 s,
        const std::vector<std::vector<int>>& points,
        const u32 k) noexcept
    {
        static u32 flat[15'001];
        u32 n = 0, p = s * 4;
        for (auto& pt : points)
        {
            u32 x = cast<u32>(pt[0]), y = cast<u32>(pt[1]);
            u32 t = x + y;
            flat[n++] = iif(x == 0 || y == s, p - t, t);
        }

        std::sort(flat, flat + n);
        *(flat + n) = *(flat + n - 1);

        static std::pair<u32, u32> dp[15'001];
        dp[n] = {0, 0};

        return *std::ranges::lower_bound(
            std::views::iota(1u, s + 1) | std::views::reverse,
            true,
            std::less{},
            [&] [[gnu::always_inline]] (u32 d) noexcept -> bool
            {
                u32 i = n - 1, j = n;
                while (true)
                {
                    u32 v = flat[i];

                    if (j != i && flat[j - 1] - v >= d)
                    {
                        --j;
                        continue;
                    }

                    auto& [cnt, last] = dp[i] = dp[j];
                    last = std::max(last, v);
                    ++cnt;

                    if (cnt == k && p + v - last >= d)
                    {
                        return true;
                    }

                    if (!i--) break;
                }

                return false;
            });
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
