#include <string>

class Solution
{
public:
    [[nodiscard]] constexpr int minSteps(
        const std::string& s,
        const std::string& t) const noexcept
    {
        int f[26]{};
        for (char c : s) ++f[c - 'a'];
        for (char c : t) --f[c - 'a'];
        int r = 0;
        for (int x : f) r += std::max(x, 0);
        return r;
    }
};
