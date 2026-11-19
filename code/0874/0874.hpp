#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "hash_set.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard, gnu::always_inline]] static constexpr u32 pack(
        i16 a,
        i16 b) noexcept
    {
        return (u32{std::bit_cast<u16>(a)} << 16) | u32{std::bit_cast<u16>(b)};
    }

    int robotSim(
        const std::vector<int>& commands,
        std::vector<std::vector<int>>& in_obstacles)
    {
        static u32 data[1 << 14];
        HashSet<1 << 14, u32, ~u32{}> obstacles{data};
        obstacles.Init();

        for (auto& obstacle : in_obstacles)
        {
            obstacles.add(pack(
                static_cast<i16>(obstacle[0]),
                static_cast<i16>(obstacle[1])));
        }

        int dx = 0, dy = 1;
        int px = 0, py = 0;
        int max_dist_sq = 0;

        for (size_t i = 0; i != commands.size();)
        {
            int c = commands[i];
            if (c < 0)
            {
                std::swap(dx, dy);

                bool cw = c == -1;
                dy = iif(cw, -dy, dy);
                dx = iif(cw, dx, -dx);
                ++i;
                continue;
            }

            int command = 0;
            while (i != commands.size() && commands[i] > 0)
            {
                command += commands[i];
                ++i;
            }

            // move
            while (command != 0)
            {
                const int tx = px + dx, ty = py + dy;
                if (obstacles.contains(
                        pack(static_cast<i16>(tx), static_cast<i16>(ty))))
                {
                    break;
                }
                px = tx, py = ty;
                --command;
            }

            max_dist_sq = std::max(px * px + py * py, max_dist_sq);
        }

        return max_dist_sq;
    }
};
