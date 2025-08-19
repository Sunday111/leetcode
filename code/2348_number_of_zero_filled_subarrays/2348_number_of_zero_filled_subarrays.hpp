#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr auto zeroFilledSubarray(
        const std::vector<int>& nums) noexcept
    {
        uint64_t r = 0, n = 0;
        for (auto v : nums)
        {
            ++n;
            n *= (v == 0);
            r += n;
        }

        return r;
    }
};
