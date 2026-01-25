#include <algorithm>
#include <vector>

#include "bitset_priority_queue.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 minPairSum(
        std::vector<u32>& nums) noexcept
    {
        static BitsetPriorityQueue<100'000, 100'000> q;
        for (u32 v : nums) q.add(v);

        u32 r = 0;
        while (!q.is_empty())
        {
            auto a = q.pop_max();
            auto b = q.pop_min();
            r = std::max(r, a + b);
        }

        return r;
    }

    [[nodiscard]] static constexpr u32 minPairSum(
        std::vector<int>& nums) noexcept
    {
        return minPairSum(reinterpret_cast<std::vector<u32>&>(nums));
    }
};

#include "sync_stdio.hpp"
