#include <ranges>
#include <vector>

#include "cast.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    bool containsCycle(const std::vector<std::vector<char>>& g) noexcept
    {
        static u32 p[500 * 500];

        auto find = [] [[gnu::always_inline]] (u32 x) noexcept
        {
            return p[p[x]];
        };

        auto merge = [find] [[gnu::always_inline]] (u32 x, u32 y) noexcept
        {
            p[find(y)] = find(x);
        };

        char left = g[0][0];
        for (u32 x = 1; char c : g[0] | std::views::drop(1))
        {
            p[x] = iif(c == left, p[x - 1], x);
            left = c;
            ++x;
        }

        u32 ti = 0, ci = cast<u32>(g[0].size()), li = ci - 1;

        for (auto [prev_row, curr_row] : g | std::views::adjacent<2>)
        {
            left = 0;
            for (auto [top, curr] : std::views::zip(prev_row, curr_row))
            {
                p[ci] = ci;
                if (left == curr)
                {
                    merge(li, ci);
                }

                if (top == curr)
                {
                    if (find(ti) == find(ci)) return true;
                    merge(ti, ci);
                }

                left = curr, ++ti, ++ci, ++li;
            }
        }

        return false;
    }
};
