#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

class Solution
{
public:
    static constexpr std::array<uint16_t, 3> kFactors{2, 3, 5};

    static constexpr auto kUglyNumbers = []()
    {
        std::array<uint32_t, 1691> dp;  // NOLINT
        dp[0] = 1;

        std::array<uint16_t, kFactors.size()> indices{};
        std::array<uint32_t, kFactors.size()> next{};

        for (size_t i = 1; i != dp.size(); ++i)
        {
            for (size_t j = 0; j != indices.size(); ++j)
            {
                next[j] = dp[indices[j]] * kFactors[j];
            }

            auto min_next = *std::ranges::min_element(next);
            dp[i] = min_next;

            for (size_t j = 0; j != indices.size(); ++j)
            {
                if (next[j] == min_next)
                {
                    ++indices[j];
                }
            }
        }
        return dp;
    }();

    [[nodiscard]] static constexpr uint32_t nthUglyNumber(uint16_t n)
    {
        return kUglyNumbers[n - 1];
    }
};
