#pragma once

#include <array>
#include <bitset>
#include <string>
#include <string_view>

class Solution
{
public:
    using u8 = uint8_t;

    [[nodiscard]] static constexpr u8 toIndex(char c) noexcept
    {
        return (c - 'a') & 0xFF;
    }

    [[nodiscard]] static constexpr char toChar(u8 c) noexcept
    {
        return static_cast<char>(c + 'a');
    }

    [[nodiscard]] static constexpr std::string smallestEquivalentString(
        std::string_view s1,
        std::string_view s2,
        std::string baseStr) noexcept
    {
        std::array<std::bitset<26>, 26> t;

        size_t n = std::min(s1.size(), s2.size());
        for (size_t i = 0; i != n; ++i)
        {
            const u8 ia = toIndex(s1[i]), ib = toIndex(s2[i]);
            if (ia != ib) t[ia][ib] = true, t[ib][ia] = true;
        }

        std::array<char, 26> remap;  // NOLINT
        for (u8 i = 0; i != t.size(); ++i)
        {
            std::bitset<26> queue = t[i];
            std::bitset<26> visited;
            visited[i] = true;
            uint8_t min_index = i;

            while (queue.count())
            {
                u8 next = std::countr_zero(queue.to_ulong()) & 0xFF;
                visited[next] = true;
                min_index = std::min(min_index, next);
                queue |= t[next];
                queue &= ~visited;
            }

            remap[i] = toChar(min_index);
        }

        for (char& c : baseStr) c = remap[toIndex(c)];

        return baseStr;
    }
};
