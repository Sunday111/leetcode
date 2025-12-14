#include <string_view>

#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr u32 kMOD = 1'000'000'007;

    [[nodiscard]] static constexpr u32 numberOfWays(
        std::string_view str) noexcept
    {
        u32 s = 0, p = 0;

        {
            u32 i = 0;
            while (i != str.size() && s != 2)
            {
                s += str[i++] == 'S';
            }
            str = str.substr(i);
        }

        u64 r = std::exchange(s, 0) == 2;

        for (char c : str)
        {
            if (c == 'S')
            {
                ++s;
                if (s % 2 == 0)
                {
                    // close
                    r *= u64{p + 1};
                    r %= kMOD;
                    s = 0;
                    p = 0;
                }
            }
            else
            {
                p += !s;
            }
        }

        return s & 1 ? 0 : static_cast<u32>(r);
    }
};
