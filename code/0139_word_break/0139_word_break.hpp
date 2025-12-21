#include <bitset>
#include <span>
#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr bool wordBreak(
        std::string_view s,
        std::span<const std::string> words) noexcept
    {
        std::bitset<320> dp;
        u16 n = s.size() & 0xFFFF;
        dp[0] = true;
        for (u16 i = 0; i != n; ++i)
        {
            if (dp[i])
            {
                for (auto& word : words)
                {
                    if (s.substr(i).starts_with(word))
                    {
                        dp[i + word.size()] = true;
                    }
                }
            }
        }

        return dp[n];
    }
};
