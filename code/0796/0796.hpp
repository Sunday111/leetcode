#include <string_view>

class Solution
{
public:
    [[nodiscard]] constexpr bool rotateString(
        std::string_view s,
        std::string_view t) const noexcept
    {
        if (s.size() == t.size())
        {
            for (auto i = s.find(t[0]); i != s.npos; i = s.find(t[0], i + 1))
            {
                if (t.starts_with(s.substr(i)) && t.ends_with(s.substr(0, i)))
                {
                    return true;
                }
            }
        }

        return false;
    }
};
