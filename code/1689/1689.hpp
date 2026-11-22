#include <algorithm>
#include <string_view>

class Solution
{
public:
    [[nodiscard]] static constexpr int minPartitions(std::string_view n) noexcept
    {
        return std::ranges::max(n) - '0';
    }
};
