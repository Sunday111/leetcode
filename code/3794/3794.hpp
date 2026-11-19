#include <algorithm>
#include <ranges>
#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string reversePrefix(
        std::string& s,
        unsigned k) noexcept
    {
        std::ranges::reverse(s | std::views::take(k));
        return std::move(s);
    }
};
