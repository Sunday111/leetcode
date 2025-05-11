#pragma once

#include <vector>

class Solution
{
public:
    uint32_t nthSuperUglyNumber(uint32_t n, const std::vector<int>& primes)
    {
        std::vector<uint32_t> dp(n);
        dp[0] = 1;

        std::vector<uint16_t> indices(primes.size());
        std::vector<uint32_t> next;
        next.reserve(primes.size());
        for (auto prime : primes)
        {
            next.push_back(std::bit_cast<uint32_t>(prime));
        }

        uint32_t min = next.front();
        for (size_t i = 1; i != dp.size(); ++i)
        {
            dp[i] = min;

            auto new_min = std::numeric_limits<uint32_t>::max();
            for (size_t j = 0; j != indices.size(); ++j)
            {
                auto& next_j = next[j];
                if (next_j == min)
                {
                    const auto& index_j = ++indices[j];
                    next_j = dp[index_j] * std::bit_cast<uint32_t>(primes[j]);
                }

                if (next_j < new_min) new_min = next_j;
            }

            min = new_min;
        }

        return dp[n - 1];
    }
};
