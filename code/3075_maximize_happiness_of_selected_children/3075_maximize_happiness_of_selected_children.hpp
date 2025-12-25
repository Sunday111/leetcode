#include <vector>

#include "radix_sorter.hpp"
#include "reinterpret_range.hpp"

class Solution
{
public:
    long long maximumHappinessSum(std::vector<int>& happiness, u32 k)
    {
        auto h = reinterpret_range<u32>(happiness);
        radix_sort<9, 3, SortOrder::Descending, 200'001>(h);
        i64 r = 0;
        for (u32 i = 0; i != k && h[i] > i; ++i) r += h[i] - i;
        return r;
    }
};
