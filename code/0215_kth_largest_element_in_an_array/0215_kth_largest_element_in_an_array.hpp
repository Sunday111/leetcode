#include <vector>

#include "bitset_heap.hpp"

class Solution
{
public:
    static constexpr u32 kValueLimit = 20'002;
    BitsetHeap<kValueLimit> heap{};

    [[nodiscard]] constexpr int findKthLargest(
        const std::vector<int>& nums,
        const u32 k) noexcept
    {
        for (u32 i = 0; i != k; ++i)
        {
            heap.add(to<u32>(nums[i] + 10'000));
        }

        const u32 n = to<u32>(nums.size());
        for (u32 i = k; i != n; ++i)
        {
            heap.add(to<u32>(nums[i] + 10'000));
            heap.pop_min();
        }

        return to<int>(heap.min()) - 10'000;
    }
};
