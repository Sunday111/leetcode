#include <ranges>
#include <vector>

#include "bitset_priority_queue.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    int minOperations(std::vector<std::vector<int>>& g, int x)
    {
        BitsetPriorityQueue<10'000, 100'000> b{};

        int tm = g.front().front() % x;
        for (int v : g | std::views::join)
        {
            [[unlikely]] if ((v % x) != tm)
            {
                return -1;
            }

            b.add(v & 0xFFFF);
        }

        u32 m = static_cast<u32>(g.size() * g.front().size()) / 2;
        for (u32 i = 0; i != m; ++i) b.pop_min();

        int t = b.min();

        int r = 0;
        for (int v : g | std::views::join)
        {
            r += std::abs(t - v) / x;
        }
        return r;
    }
};
