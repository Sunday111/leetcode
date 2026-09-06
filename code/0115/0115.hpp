#include <algorithm>
#include <string_view>
#include <utility>

using u32 = uint32_t;

class Solution
{
public:
    u32 numDistinct(std::string_view s, std::string_view t) const noexcept
    {
        const u32 ns = static_cast<u32>(s.size());
        const u32 nt = static_cast<u32>(t.size());
        u32 dp[1001];
        std::fill_n(dp, ns + 1, 1);

        for (u32 ti = nt; ti--;)
        {
            u32 o = std::exchange(dp[ns], 0u), p = 0;
            for (u32 si = ns; si--;)
            {
                u32 x = -u32{s[si] == t[ti]};
                o = std::exchange(dp[si], p += (o & x));
            }
        }

        return dp[0];
    }
};
