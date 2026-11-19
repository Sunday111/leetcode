#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 findFinalValue(
        std::vector<int>& nums,
        u32 original) noexcept
    {
        int ko = std::countr_zero(original);
        unsigned base = original >> ko, bits = 0;
        for (int v : nums)
        {
            u32 uv = static_cast<u32>(v);
            int k = std::countr_zero(uv);
            uv >>= k;
            bits |= u32{uv == base} << k;
        }

        return original << std::countr_one(bits >> ko);
    }
};
