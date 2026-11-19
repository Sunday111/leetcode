#pragma once

#include <array>
#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr int maxDifference(
        const std::string& s) noexcept
    {
        std::array<int, 26> cnt{};
        for (char c : s) ++cnt[static_cast<size_t>(c - 'a')];

        int max_odd = -1, min_even = 100;
        for (int v : cnt)
        {
            if (v)
            {
                if (v & 1)
                {
                    max_odd = std::max(v, max_odd);
                }
                else
                {
                    min_even = std::min(v, min_even);
                }
            }
        }

        return max_odd - min_even;
    }
};
