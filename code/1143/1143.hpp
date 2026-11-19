#include <string_view>

#include "largest_common_subsequence.hpp"

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] u16 longestCommonSubsequence(
        std::string_view a,
        std::string_view b) noexcept
    {
        u16 dp[2000];
        auto subseq = lcs_length<char, 1000>({dp}, a, b);

        return static_cast<u16>(subseq);
    }
};
