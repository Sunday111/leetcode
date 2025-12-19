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

        u8 dp[2][101];
        u8 *curr = dp[0], *prev = dp[1];

        curr[0] = 0;
        for (u8 i2 = 0; i2 != l2; ++i2)
        {
            curr[i2 + 1] = curr[i2] + (s2[i2] == s3[curr[i2]]);
        }

        for (u8 i1 = 0; i1 != l1; ++i1)
        {
            std::swap(curr, prev);
            char c1 = s1[i1];

            curr[0] = prev[0] + (c1 == s3[prev[0]]);
            for (u8 i2 = 0; i2 != l2; ++i2)
            {
                char c2 = s2[i2];
                curr[i2 + 1] = std::max<u8>(
                    curr[i2] + (c2 == s3[curr[i2]]),
                    prev[i2 + 1] + (c1 == s3[prev[i2 + 1]]));
            }
        }

        return curr[l2] == l3;
    }
};
