#pragma once

#include <algorithm>
#include <array>
#include <string_view>

class Solution
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;

    [[nodiscard]] static constexpr u32 minimumDeletions(
        std::string_view word,
        u32 k) noexcept
    {
        constexpr u8 n = 26;
        std::array<u32, n> freqs{};
        for (char c : word) ++freqs[(c - 'a') & 0xFF];
        std::ranges::sort(freqs);

        u32 min_remove = std::numeric_limits<u32>::max();
        u32 prefix_sum = 0;

        u8 i = 0;

        while (i != n && freqs[i] == 0) ++i;

        for (; i != n; ++i)
        {
            const auto limit = freqs[i] + k;

            u8 j = i + 1;
            while (j != n && freqs[j] <= limit) ++j;

            u32 overflow = 0;
            for (; j != n; ++j) overflow += freqs[j] - limit;

            min_remove = std::min(min_remove, prefix_sum + overflow);

            if (overflow == 0) break;
            prefix_sum += freqs[i];
        }

        return min_remove;
    }
};
