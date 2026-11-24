#include <vector>

#include "radix_sort/radix_sort.hpp"

class Solution
{
public:
    [[nodiscard]] static u32 getMaximumConsecutive(
        std::vector<int>& coins_) noexcept
    {
        auto* coins = reinterpret_cast<u32*>(coins_.data());
        const auto n = static_cast<u32>(coins_.size());
        radix_sort<16, 8>(coins, n);
        u32 x = 0, i = 0;
        while (i != n && coins[i] <= x + 1) x += coins[i++];
        return x + 1;
    }
};
