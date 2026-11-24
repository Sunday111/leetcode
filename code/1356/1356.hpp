#include <bit>

#include "radix_sort/radix_sort.hpp"

class Solution
{
public:
    static std::vector<int> sortByBits(std::vector<int>& arr)
    {
        auto au = reinterpret_range<u32>(arr);

        for (u32& x : au)
        {
            x = (static_cast<u32>(std::popcount(x)) << 16) | x;
        }

        radix_sort<8>(au);

        for (u32& x : au)
        {
            x &= 0xFFFF;
        }

        return std::move(arr);
    }
};
