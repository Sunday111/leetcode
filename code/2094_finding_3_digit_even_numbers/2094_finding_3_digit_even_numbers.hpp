#pragma once

#include <array>
#include <cstdint>
#include <vector>

class Solution
{
public:
    std::vector<int> findEvenNumbers(std::vector<int>& digits)
    {
        std::array<uint8_t, 10> cnt{};
        for (auto digit : digits) cnt[static_cast<uint8_t>(digit)]++;

        if (cnt[0] + cnt[2] + cnt[4] + cnt[6] + cnt[8] == 0) return {};

        std::vector<int> r;
        r.reserve(500);

        for (uint8_t i = 1; i != 10; ++i)
        {
            auto& ci = cnt[i];
            if (ci == 0) continue;
            --ci;

            for (uint8_t j = 0; j != 10; ++j)
            {
                auto& cj = cnt[j];
                if (cj == 0) continue;
                --cj;

                for (uint8_t k = 0; k != 10; k += 2)
                {
                    if (cnt[k] != 0)
                    {
                        r.push_back(100 * i + 10 * j + k);
                    }
                }

                ++cj;
            }

            ++ci;
        }

        return r;
    }
};
