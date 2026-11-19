#include <string_view>

class Solution
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;
    u32 numDecodings(std::string_view s) noexcept
    {
        u8 n = s.size() & 0xFF;
        u32 dp[2]{1, s[0] != '0'};
        for (u8 prev = (s[0] - '0') & 0xF, i = 1; i != n; ++i)
        {
            u8 curr = (s[i] - '0') & 0xF;
            u32 ba = !!curr;
            (prev *= 10) += curr;
            u32 bb = (prev > 9 && prev < 27);
            u32 pop = std::exchange(dp[0], dp[1]);
            dp[1] = (dp[0] & -ba) + (pop & -bb);
            prev = curr;
        }

        return dp[1];
    }
};
