#include <ranges>
#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string mapWordWeights(
        const std::vector<std::string>& words,
        const std::vector<int>& weights) noexcept
    {
        return std::ranges::to<std::string>(
            words | std::views::transform(
                        [&](const std::string& word)
                        {
                            int s = 0;
                            for (char c : word) s += weights[(c - 'a') & 0xFF];
                            return static_cast<char>('z' - (s % 26));
                        }));
    }
};
