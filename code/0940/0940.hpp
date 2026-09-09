#include <string_view>

class Solution
{
public:
    inline static constexpr int m = 1'000'000'007;
    auto distinctSubseqII(std::string_view s)
    {
        long f[32]{}, g{1};
        for (auto x : s)
        {
            g = (2 * g - std::exchange(f[(x - 'a') & 31], g)) % m;
        }
        return (g + m - 1) % m;
    }
};
