#include <cstdlib>
#include <string_view>

class Solution
{
public:
    bool sumGame(std::string_view str)
    {
        const size_t n = str.size(), half = n / 2;
        int q{}, d{};
        for (size_t i = 0; i != n; ++i)
        {
            int c = str[i] & 127;
            int g = c != '?';
            int u = (c - '0') & -g;
            int j = i >= half;
            q += g - ((2 * g) & -j);
            d += u - ((2 * u) & -j);
        }

        return (q & 1) || 2 * d != 9 * q;
    }
};
