#include <vector>

#include "radix_sort/radix_sort.hpp"
#include "signed_integral_aliases.hpp"

class Solution
{
public:
    long long maximumHappinessSum(std::vector<int>& happiness, u32 k)
    {
        auto* h = reinterpret_cast<u32*>(happiness.data());
        radix_sort<27, 9, SortOrder::Descending, 200'001>(
            h,
            static_cast<u32>(happiness.size()));
        i64 r = 0;
        for (u32 i = 0; i != k && h[i] > i; ++i) r += h[i] - i;
        return r;
    }
};
