#include <algorithm>
#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string largestEven(
        std::string& s) noexcept
    {
        auto it = std::begin(std::ranges::find_last(s, '2'));
        s.erase(it == std::end(s) ? s.begin() : std::next(it), s.end());
        return std::move(s);
    }
};
