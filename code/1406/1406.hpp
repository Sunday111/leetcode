#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

#include "sync_stdio.hpp"

using namespace std::string_view_literals;  // NOLINT

class Solution
{
public:
    inline static constexpr std::string_view kAns[]{
        "Bob"sv,
        "Tie"sv,
        "Alice"sv,
    };
    std::string stoneGameIII(const std::vector<int>& sv) noexcept
    {
        int dp[3]{}, x[2]{};
        for (int v : sv | std::views::reverse)
        {
            int r = std::max(
                std::max(v - dp[0], v + x[0] - dp[1]),
                v + x[0] + x[1] - dp[2]);
            x[1] = std::exchange(x[0], v);
            dp[2] = std::exchange(dp[1], std::exchange(dp[0], r));
        }

        return std::string(kAns[std::clamp(dp[0], -1, 1) + 1]);
    }
};
