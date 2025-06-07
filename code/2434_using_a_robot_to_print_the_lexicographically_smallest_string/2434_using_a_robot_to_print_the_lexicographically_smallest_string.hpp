#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <string>

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;

    [[nodiscard]] ATTR static constexpr u8 to_idx(char c) noexcept
    {
        return static_cast<u8>(c - 'a');
    }

    [[nodiscard]] ATTR static constexpr std::string robotWithString(
        std::string s) noexcept
    {
        std::string t;
        t.reserve(s.size());

        std::array<u32, 26> cnt{};
        for (char c : s) ++cnt[to_idx(c)];

        u8 smallest_index = 0;
        while (!cnt[smallest_index]) ++smallest_index;

        u32 out = 0;
        for (char c : s)
        {
            const u8 ci = to_idx(c);
            --cnt[ci];
            if (ci != smallest_index)
            {
                t.push_back(c);
                continue;
            }

            s[out++] = c;
            while (smallest_index != cnt.size() && cnt[smallest_index] == 0)
            {
                ++smallest_index;
            }

            while (!t.empty() && to_idx(t.back()) <= smallest_index)
            {
                s[out++] = t.back();
                t.pop_back();
            }
        }

        return s;
    }
};
