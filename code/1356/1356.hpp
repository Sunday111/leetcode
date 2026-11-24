#include <bit>
#include <span>
#include <vector>

#include "radix_sort/radix_sort.hpp"

class Solution
{
public:
    static std::vector<int> sortByBits(std::vector<int>& arr)
    {
        auto* data = reinterpret_cast<u32*>(arr.data());
        const auto n = static_cast<u32>(arr.size());
        const std::span au{data, n};

        for (u32& x : au)
        {
            x = (static_cast<u32>(std::popcount(x)) << 16) | x;
        }

        radix_sort<32, 8>(data, n);

        for (u32& x : au)
        {
            x &= 0xFFFF;
        }

        return std::move(arr);
    }
};
