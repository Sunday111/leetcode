#pragma once

#include <string>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

class Solution
{
public:
    using u32 = uint32_t;

    template <char cx, char cy>
    [[nodiscard]] FORCE_INLINE static constexpr u32 one_pass(
        std::string& s,
        u32 x) noexcept
    {
        u32 l = 0;
        u32 n = static_cast<u32>(s.size());

        for (u32 i = 0; i != n; ++i)
        {
            char c = s[i];
            if (l != 0 && s[l - 1] == cx && c == cy)
            {
                --l;
            }
            else
            {
                s[l++] = c;
            }
        }

        u32 score = x * ((n - l) / 2);
        s.resize(l);
        return score;
    }

    template <char cx, char cy>
    [[nodiscard]] FORCE_INLINE static constexpr u32
    impl(std::string& s, u32 x, u32 y) noexcept
    {
        u32 r = one_pass<cx, cy>(s, x);
        return r + one_pass<cy, cx>(s, y);
    }

    [[nodiscard]] FORCE_INLINE static constexpr u32
    maximumGain(std::string& s, u32 x, u32 y) noexcept
    {
        if (x > y)
        {
            return impl<'a', 'b'>(s, x, y);
        }
        else
        {
            return impl<'b', 'a'>(s, y, x);
        }
    }
};
