#include <string>

#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr std::string stringHash(
        std::string& s,
        u8 k) noexcept
    {
        u16 t = 0;

        for (u16 h = 0, l = 0; char c : s)
        {
            u16 b = ++l != k;
            h += (c - 'a') & 31;
            h -= (26 & -(h >= 26));  // h %= 26
            s[t] = (h + 'a') & 127;  // NOLINT
            t += !b;
            h &= -b;
            l &= -b;
        }

        s.resize(t);
        return std::move(s);
    }
};
