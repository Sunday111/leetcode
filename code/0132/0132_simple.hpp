#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;

    static int minCut(std::string_view s) noexcept
    {
        static u16 dp[2001];

        const u16 n = s.size() & 0xFFFF;
        dp[n] = 0;

        auto isPalindrome = [&](u16 first, u16 last)
        {
            while (first < last)
            {
                if (s[first] != s[last]) return false;
                ++first, --last;
            }

            return true;
        };

        for (u16 i = n; i--;)
        {
            auto& dpi = dp[i] = 2000;

            for (u16 j = i; j != n; ++j)
            {
                if (isPalindrome(i, j))
                {
                    dpi = std::min<u16>(dpi, dp[j + 1] + 1);
                }
            }
        }

        return dp[0] - 1;
    }
};
