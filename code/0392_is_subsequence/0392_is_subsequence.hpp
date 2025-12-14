#include <string_view>

class Solution
{
public:
    [[nodiscard]] static constexpr bool isSubsequence(
        const std::string_view s,
        const std::string_view t) noexcept
    {
        size_t t_pos = 0;
        for (char c : s)
        {
            auto x = t.find(c, t_pos);
            if (x == t.npos) return false;
            t_pos = x + 1;
        }

        return true;
    }
};
