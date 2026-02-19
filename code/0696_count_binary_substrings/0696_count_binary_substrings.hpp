#include <string>

class Solution
{
public:
    [[nodiscard]] constexpr int countBinarySubstrings(
        const std::string& s) noexcept
    {
        int np = 0, nc = 0, ans = 0;

        for (char curr = 0; char c : s)
        {
            if (c != curr)
            {
                ans += std::min(np, nc);
                np = nc;
                curr = c;
                nc = 0;
            }
            ++nc;
        }

        ans += std::min(np, nc);

        return ans;
    }
};
