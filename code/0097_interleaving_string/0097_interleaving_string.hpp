#include <algorithm>
#include <string_view>

class Solution
{
public:
    using u8 = uint8_t;
    static bool isInterleave(
        std::string_view s1,
        std::string_view s2,
        std::string_view s3) noexcept
    {
        u8 l1 = s1.size() & 0xFF, l2 = s2.size() & 0xFF, l3 = s3.size() & 0xFF;

        if (l1 + l2 != l3) return false;

        u8 dp[101];
        dp[0] = 0;
        for (u8 i2 = 0; i2 != l2; ++i2)
        {
            dp[i2 + 1] = dp[i2] + (s2[i2] == s3[dp[i2]]);
        }

        for (u8 i1 = 0; i1 != l1; ++i1)
        {
            char c1 = s1[i1];
            dp[0] = dp[0] + (c1 == s3[dp[0]]);
            for (u8 i2 = 0; i2 != l2; ++i2)
            {
                dp[i2 + 1] = std::max<u8>(
                    dp[i2] + (s2[i2] == s3[dp[i2]]),
                    dp[i2 + 1] + (c1 == s3[dp[i2 + 1]]));
            }
        }

        return dp[l2] == l3;
    }
};
