#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"
#include "radix_sorter.hpp"
#include "sync_stdio.hpp"

class Solution
{
public:
    u64 minSumSquareDiff(
        std::vector<int>& nums1,
        const std::vector<int>& nums2,
        u64 k1,
        u64 k2)
    {
        u32* const a = reinterpret_cast<u32*>(nums1.data());
        const u32* const b = reinterpret_cast<const u32*>(nums2.data());

        const u32 n = nums1.size() & ~0u;

        for (u32 i = 0; i != n; ++i)
        {
            u32 v1 = a[i];
            u32 v2 = b[i];
            u32 diff = std::max(v1, v2) - std::min(v1, v2);
            a[i] = diff;
        }

        radix_sort<8, 4, SortOrder::Descending>(std::span{a, n});

        u64 k = k1 + k2;
        u64 level = a[0];

        u32 count = 1;
        for (; count <= n; ++count)
        {
            u64 next = count < n ? a[count] : 0;
            u64 cost = (level - next) * count;
            if (k < cost)
            {
                break;
            }

            k -= cost;
            level = next;
        }

        u64 sum{};

        if (level)
        {
            level -= k / count;
            u64 remainder = k % count;
            sum = level * level * (count - remainder) +
                  (level - 1) * (level - 1) * remainder;
            for (u32 i = count; i < n; ++i)
            {
                sum += u64{a[i]} * a[i];
            }
        }

        return sum;
    }
};
