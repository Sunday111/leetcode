#include <algorithm>
#include <vector>

#include "radix_sorter.hpp"
#include "reinterpret_range.hpp"

using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard, gnu::always_inline]] static constexpr u64 pack(
        int b,
        int a) noexcept
    {
        return (u64{std::bit_cast<u32>(a)} << 32) | u64{std::bit_cast<u32>(b)};
    }

    [[nodiscard, gnu::always_inline]] static constexpr std::tuple<int, int>
    unpack(u64 p) noexcept
    {
        u32 b = (p >> 32) & ~u32{};
        u32 a = (p >> 0) & ~u32{};
        return {std::bit_cast<int>(a), std::bit_cast<int>(b)};
    }

    u32 maxWalls(
        std::vector<int>& positions,
        std::vector<int>& distances,
        std::vector<int>& walls) noexcept
    {
        u32 nr = static_cast<u32>(positions.size());
        u32 nw = static_cast<u32>(walls.size());

        static u64 robots[100'002];

        robots[0] = pack(0, 0);
        for (u32 i = 0; i != nr; ++i)
        {
            robots[i + 1] = pack(positions[i], distances[i]);
        }
        robots[nr + 1] = pack(INT_MAX, 0);

        radix_sort<10, 3>(std::span{robots + 1, nr});
        radix_sort<10, 3>(reinterpret_range<u32>(std::span{walls}));

        int* we = walls.data() + nw;
        int *a = walls.data(), *c = a;
        int* b = walls.data();

        u32 na = 0, nb = 0;

        auto dist =
            [] [[nodiscard, gnu::always_inline]] (auto a, auto b) noexcept
        {
            return static_cast<u32>(std::distance(a, b));
        };

        for (u32 ri = 1; ri != nr + 1; ++ri)
        {
            auto [p, d] = unpack(robots[ri]);
            int l = p - d;
            int r = p + d;

            {
                auto [prev, _1] = unpack(robots[ri - 1]);
                l = std::max(l, prev + 1);
                auto [next, _2] = unpack(robots[ri + 1]);
                r = std::min(r, next - 1);
            }

            // add reachable
            while (c != we && *c <= r) ++c;

            // remove unreachable
            while (a != c && *a < l) ++a;
            b = std::max(a, b);

            auto at_robot = a;
            while (at_robot != c && *at_robot < p) ++at_robot;

            auto after_robot = at_robot + (at_robot != c && *at_robot == p);
            u32 lla = na + dist(a, after_robot);
            u32 lra = na + dist(at_robot, c);
            u32 llb = nb + dist(b, after_robot);
            u32 lrb = nb + dist(at_robot, c);

            a = after_robot;
            b = c;

            na = std::max(lla, llb);
            nb = std::max(lra, lrb);
        }
        return std::max(na, nb);
    }
};
