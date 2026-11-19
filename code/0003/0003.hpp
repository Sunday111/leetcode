#pragma once

#include <algorithm>
#include <array>
#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr u16 lengthOfLongestSubstring(
        std::string_view s) noexcept
    {
        std::array<u16, 256> freq{};
        const auto n = static_cast<u16>(s.size());
        u16 max_len = 0, l = 0, r = 0;
        while (r != n)
        {
            auto& cnt = ++freq[s[r] & 0x7F];
            while (cnt > 1) --freq[s[l++] & 0x7F];
            max_len = std::max<u16>(max_len, ++r - l);
        }
        return max_len;
    }
};
