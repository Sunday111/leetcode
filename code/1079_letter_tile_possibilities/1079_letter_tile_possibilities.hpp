#include <string_view>

#include "integral_aliases.hpp"

struct Solution
{
    [[nodiscard]] static constexpr u32 numTilePossibilities(
        std::string_view s) noexcept
    {
        u8 freq[7]{}, max_freq[26]{};
        u8 n = 0, l = 0, i = 0;
        u32 r = 0;

        for (char c : s) ++max_freq[c - 'A'];

        for (u8 cnt : max_freq)
        {
            max_freq[n] = cnt;
            n += !!cnt;
        }

        [&](this auto&& dfs) -> void
        {
            if (i == n)
            {
                constexpr u16 f[]{1, 1, 2, 6, 24, 120, 720, 5040};
                u16 d = 1;
                for (u8 j = 0; j != i; ++j) d *= f[freq[j]];
                r += f[l] / d;
            }
            else
            {
                freq[i] = 0;
                while (freq[i] <= max_freq[i])
                {
                    ++i;
                    dfs();
                    --i;
                    ++l;
                    ++freq[i];
                }
                l -= freq[i];
            }
        }();

        return r - 1;
    }
};
