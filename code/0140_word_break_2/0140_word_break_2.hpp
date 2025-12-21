#include <array>
#include <ranges>
#include <span>
#include <string_view>
#include <vector>

// 1 <= wordDict.length <= 1000
// 1 <= s.length <= 20
// 1 <= wordDict[i].length <= 10

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;

    [[nodiscard]] static constexpr std::vector<std::string> wordBreak(
        std::string_view s,
        std::span<const std::string> words) noexcept
    {
        const u8 n = s.size() & 0xFF;
        std::array<std::vector<std::vector<std::string>>, 21> dp;
        dp[n].emplace_back().push_back("");

        for (u8 i = n; i--;)
        {
            auto& dpi = dp[i];
            for (auto& word : words)
            {
                if (s.substr(i).starts_with(word))
                {
                    for (auto& path : dp[i + word.size()])
                    {
                        dpi.emplace_back() = path;
                        dpi.back().push_back(word);
                    }
                }
            }
        }

        return std::ranges::to<std::vector>(
            dp[0] | std::views::transform(
                        [&](std::vector<std::string>& path)
                        {
                            std::string s = path.back();

                            for (size_t i = path.size() - 2; i; --i)
                            {
                                s += ' ';
                                s += path[i];
                            }

                            return s;
                        }));
    }
};
