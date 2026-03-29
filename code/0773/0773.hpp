// https://leetcode.com/problems/sliding-puzzle/

#include <bit>
#include <ranges>
#include <unordered_set>
#include <vector>

using u32 = uint32_t;
struct State
{
    u32 v00 : 3 = 0;
    u32 v01 : 3 = 0;
    u32 v02 : 3 = 0;
    u32 v10 : 3 = 0;
    u32 v11 : 3 = 0;
    u32 v12 : 3 = 0;
    u32 zi : 3 = 0;
    u32 empty_ : 32 - 21 = 0;
};
static_assert(sizeof(State) == sizeof(int));

class Solution
{
public:
    inline static constexpr State kTarget{
        .v00 = 1,
        .v01 = 2,
        .v02 = 3,
        .v10 = 4,
        .v11 = 5,
        .v12 = 0,
        .zi = 5,
    };

    int slidingPuzzle(std::vector<std::vector<int>>& brd)
    {
        static State q[2000];
        u32 qs = 0;
        {
            State& x = q[qs++] = State{
                .v00 = static_cast<u32>(brd[0][0]),
                .v01 = static_cast<u32>(brd[0][1]),
                .v02 = static_cast<u32>(brd[0][2]),
                .v10 = static_cast<u32>(brd[1][0]),
                .v11 = static_cast<u32>(brd[1][1]),
                .v12 = static_cast<u32>(brd[1][2]),
            };
            for (u32 i = 0; int v : brd | std::views::join)
            {
                if (v == 0) x.zi = i;
                ++i;
            }
        }

        std::unordered_set<u32> vis;

#define do_swap(a, b, z)       \
    {                          \
        auto& t = q[qs++] = x; \
        t.zi = z;              \
        t.a = x.b;             \
        t.b = x.a;             \
    }

        int r = 0;
        for (size_t qb = 0, qe = qs; qb != qe; qb = qe, qe = qs)
        {
            while (qb != qe)
            {
                auto x = q[qb++];
                if (!vis.emplace(std::bit_cast<u32>(x)).second) continue;
                if (std::bit_cast<u32>(x) == std::bit_cast<u32>(kTarget))
                {
                    return r;
                }

                switch (x.zi)
                {
                case 0:
                    do_swap(v00, v10, 3);
                    do_swap(v00, v01, 1);
                    break;

                case 1:
                    do_swap(v01, v11, 4);
                    do_swap(v01, v02, 2);
                    do_swap(v00, v01, 0);
                    break;

                case 2:
                    do_swap(v02, v12, 5);
                    do_swap(v01, v02, 1);
                    break;
                case 3:
                    do_swap(v10, v11, 4);
                    do_swap(v10, v00, 0);
                    break;
                case 4:
                    do_swap(v11, v12, 5);
                    do_swap(v11, v10, 3);
                    do_swap(v11, v01, 1);
                    break;
                case 5:
                    do_swap(v12, v02, 2);
                    do_swap(v12, v11, 4);
                    break;
                }
            }
            ++r;
        }

        return -1;
    }
};
