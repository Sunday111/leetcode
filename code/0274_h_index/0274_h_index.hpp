#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int hIndex(
        const std::vector<int>& citations) noexcept
    {
        std::array<int, 1001> freq{};
        for (int c : citations) ++freq[static_cast<uint32_t>(c)];

        int r = 0;
        for (int i = freq.size(), k = 0; i--;)
        {
            k += freq[static_cast<uint32_t>(i)];
            r = std::max(r, std::min(k, i));
        }

        return r;
    }
};
