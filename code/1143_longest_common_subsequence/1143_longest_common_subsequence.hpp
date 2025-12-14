
#include <algorithm>
#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] u16 longestCommonSubsequence(
        std::string_view a,
        std::string_view b) noexcept
    {
        u16 la = a.size() & 0xFFFF, lb = b.size() & 0xFFFF, dp[2000];
        auto curr = dp, prev = curr + 1000;
        std::fill_n(prev, lb, 0);

        for (u16 ia = 0; ia != la; ++ia)
        {
            std::swap(curr, prev);

            char ca = a[ia];

            curr[0] = ca == b[0] || prev[0];

            for (u16 ib = 1; ib != lb; ++ib)
            {
                if (ca == b[ib])
                {
                    curr[ib] = prev[ib - 1] + 1;
                }
                else
                {
                    curr[ib] = std::max(curr[ib - 1], prev[ib]);
                }
            }
        }

        return curr[lb - 1];
    }
};
