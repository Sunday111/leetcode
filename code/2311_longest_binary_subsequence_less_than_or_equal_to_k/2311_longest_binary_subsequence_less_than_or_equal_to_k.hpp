#pragma once

#include <algorithm>
#include <ranges>
#include <string_view>

class Solution
{
public:
    using u32 = uint32_t;

    [[nodiscard]] static constexpr u32 longestValidSuffix(
        std::string_view s,
        u32 k) noexcept
    {
        u32 v = 0, l = 0;
        for (char c : s | std::views::reverse | std::views::take(30))
        {
            if (c == '1')
            {
                v |= u32{1} << l;
                if (v > k) break;
            }

            ++l;
        }
        return l;
    }

    [[nodiscard]] static constexpr u32 longestSubsequence(
        std::string_view s,
        u32 k) noexcept
    {
        u32 suffix = longestValidSuffix(s, k);
        s = s.substr(0, s.size() - suffix);
        u32 prefix = static_cast<u32>(std::ranges::count(s, '0'));
        return prefix + suffix;
    }
};
