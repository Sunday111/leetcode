#include <ranges>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    bool containsCycle(const std::vector<std::vector<char>>& g) noexcept
    {
        const u32 w = cast<u32>(g[0].size());

        static u32 parent[500 * 500];

        auto find = [] [[gnu::always_inline]] (u32 x) noexcept
        {
            while (parent[x] != x)
            {
                u32& y = parent[x];
                x = y = parent[y];
            }
            return x;
        };

        auto merge = [find] [[gnu::always_inline]] (u32 x, u32 y) noexcept
        {
            parent[find(y)] = find(x);
        };

        char left = 0;
        for (u32 x = 0; char c : g[0])
        {
            parent[x] = x;
            if (c == left) merge(x - 1, x);
            left = c;
            ++x;
        }

        u32 ti = 0, ci = w, li = ci - 1;

        for (auto [prev_row, curr_row] : g | std::views::adjacent<2>)
        {
            left = 0;
            for (auto [top, curr] : std::views::zip(prev_row, curr_row))
            {
                parent[ci] = ci;
                if (left == curr)
                {
                    merge(li, ci);
                }

                if (top == curr)
                {
                    if (find(ti) == find(ci)) return true;
                    merge(ti, ci);
                }

                left = curr;
                ++ti, ++ci, ++li;
            }
        }

        return false;
    }
};
