#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] u32 getMaximumConsecutive(std::vector<int>& coins_) noexcept
    {
        auto coins = reinterpret_range<u32>(coins_);
        radix_sort<8, 2>(coins);
        u32 x = 0, i = 0;
        while (i != coins.size() && coins[i] <= x + 1) x += coins[i++];
        return x + 1;
    }
};
