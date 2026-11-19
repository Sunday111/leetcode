#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

class Solution
{
public:
    template <typename T>
    [[nodiscard]] static constexpr bool threeConsecutiveOdds(
        const std::vector<T>& arr)
    {
        uint8_t k = 0;
        for (auto v : arr)
        {
            if (v % 2)
            {
                if (++k == 3) return true;
            }
            else
            {
                k = 0;
            }
        }

        return false;
    }
};
