#include <cstdint>
#include <vector>

#include "bitsets/bitset_view/bsv_count.hpp"
#include "bitsets/bitset_view/bsv_fill.hpp"
#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"

using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    static size_t countUnguarded(
        u32 h,
        u32 w,
        std::vector<std::vector<int>>& guards_,
        std::vector<std::vector<int>>& walls_)
    {
        using U = std::vector<std::vector<u32>>;
        auto& guards = reinterpret_cast<U&>(guards_);
        auto& walls = reinterpret_cast<U&>(walls_);
        const u32 t = w * h;
        static u64 buf[200'130 / 64];
        u32 num_words = (t / 64) + 1;
        BitsetView<u64> visited{buf, t}, obstacle{buf + num_words, t};
        bsv_fill<false>(visited);
        bsv_fill<false>(obstacle);
        for (auto& g : guards) bsv_set<true>(obstacle, g[0] * w + g[1]);
        for (auto& wall : walls) bsv_set<true>(obstacle, wall[0] * w + wall[1]);
        auto visit = [&](u32 x, u32 y, u32 dx, u32 dy)
        {
            u32 i = w * y + x, o = dx ? dx : w * dy;
            x += dx, y += dy, i += o;
            while (x < w && y < h && !bsv_get(obstacle, i))
            {
                bsv_set<true>(visited, i);
                x += dx, y += dy, i += o;
            }
        };
        for (auto& g : guards)
        {
            u32 y = g[0], x = g[1];
            visit(x, y, 1, 0);
            visit(x, y, 0, 1);
            visit(x, y, ~0u, 0);
            visit(x, y, 0, ~0u);
        }

        return t - walls.size() - guards.size() - bsv_count(visited);
    }
};

#include "sync_stdio.hpp"
