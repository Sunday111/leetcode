#include <algorithm>
#include <string_view>

class Solution
{
public:
    int minimumPushes(std::string_view w) const noexcept
    {
        int f[26]{}, b{8}, r{};
        for (char c : w) ++f[c - 'a'];
        std::ranges::sort(f, std::greater{});
        for (int x : f)
        {
            r += (b >> 3) * x;
            b += !!x;
        }
        return r;
    }
};
