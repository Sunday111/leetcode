#include <array>
#include <cstdint>
#include <string>

#include "hot_path.hpp"
#include "int_if.hpp"

class Solution
{
public:
    using u16 = uint16_t;
    static u16 longestBalanced(const std::string& s) noexcept HOT_PATH
    {
        const u16 n = static_cast<u16>(s.size());

        std::array<u16, 26> freq{};
        u16 r = 0, min = 0, max = 0;
        for (u16 i = 0; i != n && r < n - i; ++i)
        {
            freq.fill(0);
            min = max = 1;
            for (u16 j = i; j != n && r < n - i; ++j)
            {
                u16& f = freq[(s[j] - 'a') & 0x1F];
                if (f++ <= min)
                {
                    min = f;
                    for (auto& v : freq)
                    {
                        min = iif(v && v < min, v, min);
                    }
                }

                max = std::max(max, f);

                u16 l = j + 1 - i;
                r = iif(min == max && l > r, l, r);
            }
        }

        return r;
    }
};

#include "sync_stdio.hpp"
