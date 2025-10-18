#include <algorithm>
#include <array>

using u8 = uint8_t;
using u64 = uint64_t;

u64 dp[20][20][2][2];
u8 digits[16];

template <u8 i, u8 l, bool za, bool zb>
inline u64 solve(u8 carry) noexcept
{
    if constexpr (i == l)
    {
        return !carry;
    }
    else
    {
        u64& cnt = dp[i][carry][za][zb];
        if (cnt != ~u64{}) return cnt;

        cnt = 0;

        constexpr u8 eda = (za ? 1 : 10), edb = (zb ? 1 : 10);
        const u8 digit = digits[i];

        if constexpr (i)
        {
            for (u8 b = 1; b != edb; ++b)
            {
                if (u8 x = b + carry; x % 10 == digit)
                {
                    cnt += solve<i + 1, l, true, zb>(x / 10);
                }
            }

            for (u8 a = 1; a != eda; ++a)
            {
                if (u8 x = a + carry; x % 10 == digit)
                {
                    cnt += solve<i + 1, l, za, true>(x / 10);
                }
            }

            if (u8 x = carry; x % 10 == digit)
            {
                cnt += solve<i + 1, l, true, true>(x / 10);
            }
        }

        for (u8 a = 1; a != eda; ++a)
        {
            for (u8 b = 1; b != edb; ++b)
            {
                if (u8 x = a + b + carry; x % 10 == digit)
                {
                    cnt += solve<i + 1, l, za, zb>(x / 10);
                }
            }
        }
        return cnt;
    }
}
class Solution  // NOLINT
{
public:
    constexpr static std::array fns{
        solve<0, 1, false, false>,
        solve<0, 2, false, false>,
        solve<0, 3, false, false>,
        solve<0, 4, false, false>,
        solve<0, 5, false, false>,
        solve<0, 6, false, false>,
        solve<0, 7, false, false>,
        solve<0, 8, false, false>,
        solve<0, 9, false, false>,
        solve<0, 10, false, false>,
        solve<0, 11, false, false>,
        solve<0, 12, false, false>,
        solve<0, 13, false, false>,
        solve<0, 14, false, false>,
        solve<0, 15, false, false>,
        solve<0, 16, false, false>,
    };

    u64 countNoZeroPairs(u64 n) noexcept
    {
        u8 l = 0;
        while (n)
        {
            digits[l++] = n % 10;
            n /= 10;
        }
        std::fill_n(dp[0][0][0], 20 * 20 * 2 * 2, ~u64{});

        return fns[l - 1](0);
    }
};
