#include <vector>

#include "bitset_priority_queue.hpp"

class Solution
{
public:
    using Queue = BitsetPriorityQueue<20'002, 100'000>;
    using ValueType = Queue::ValueType;
    using FreqType = Queue::FrequencyType;
    Queue heap{};

    [[nodiscard]] constexpr int findKthLargest(
        const std::vector<int>& nums,
        const FreqType k) noexcept
    {
        for (FreqType i = 0; i != k; ++i)
        {
            heap.add(to<ValueType>(nums[i] + 10'000));
        }

        const auto n = to<FreqType>(nums.size());
        for (FreqType i = k; i != n; ++i)
        {
            heap.add(to<ValueType>(nums[i] + 10'000));
            heap.pop_min();
        }

        return to<int>(heap.min()) - 10'000;
    }
};
