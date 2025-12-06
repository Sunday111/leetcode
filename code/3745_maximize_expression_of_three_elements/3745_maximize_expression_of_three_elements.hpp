#include <vector>

#include "bitset_priority_queue.hpp"

class Solution
{
public:
    int maximizeExpressionOfThree(std::vector<int>& nums)
    {
        BitsetPriorityQueue<200, 100> q;

        for (int v : nums)
        {
            v += 100;
            q.add(v & 0xFF);
        }

        auto a = int{q.pop_max()} - 100;
        auto b = int{q.pop_max()} - 100;
        auto c = int{q.pop_min()} - 100;

        return a + b - c;
    }
};
