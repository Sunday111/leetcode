#pragma once

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

class Solution
{
public:
    struct PairHash
    {
        template <std::integral T>
        [[nodiscard]] constexpr size_t operator()(
            const std::pair<T, T>& p) const noexcept
        {
            return std::hash<T>()(p.first) ^ (std::hash<T>()(p.second) << 1);
        }
    };

    int robotSim(
        const std::vector<int>& commands,
        std::vector<std::vector<int>>& in_obstacles)
    {
        std::unordered_set<std::pair<int16_t, int16_t>, PairHash> obstacles;
        obstacles.reserve(in_obstacles.size());

        for (auto& obstacle : in_obstacles)
        {
            obstacles.emplace(obstacle[0], obstacle[1]);
        }

        int dx = 0, dy = 1;
        int px = 0, py = 0;
        int max_dist_sq = 0;

        for (size_t i = 0; i != commands.size();)
        {
            if (commands[i] == -1)
            {
                // Turn right (CW)
                std::swap(dx, dy);
                dy = -dy;
                ++i;
                continue;
            }

            if (commands[i] == -2)
            {
                // Turn left (CCW)
                std::swap(dx, dy);
                dx = -dx;
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
                if (obstacles.contains(std::make_pair(tx, ty))) break;
                px = tx, py = ty;
                --command;
            }

            int dist_sq = px * px + py * py;
            if (dist_sq > max_dist_sq)
            {
                max_dist_sq = dist_sq;
            }
        }

        return max_dist_sq;
    }
};
