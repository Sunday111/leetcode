#pragma once

#include <algorithm>
#include <cassert>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution
{
public:
    int robotSim(
        const std::vector<int>& commands,
        std::vector<std::vector<int>>& obstacles)
    {
        std::unordered_map<int16_t, std::vector<int16_t>> obstacles_by_x;
        obstacles_by_x.reserve(obstacles.size());

        std::unordered_map<int16_t, std::vector<int16_t>> obstacles_by_y;
        obstacles_by_y.reserve(obstacles.size());

        for (auto& obstacle : obstacles)
        {
            int16_t x = static_cast<int16_t>(obstacle[0]),
                    y = static_cast<int16_t>(obstacle[1]);
            obstacles_by_x[x].push_back(y);
            obstacles_by_y[y].push_back(x);
        }

        std::ranges::for_each(
            std::views::values(obstacles_by_x),
            std::ranges::sort);
        std::ranges::for_each(
            std::views::values(obstacles_by_y),
            std::ranges::sort);

        auto get_obstacles =
            [](int coord,
               const std::unordered_map<int16_t, std::vector<int16_t>>& lookup)
            -> std::span<const int16_t>
        {
            if (std::cmp_greater_equal(
                    coord,
                    std::numeric_limits<int16_t>::lowest()) &&
                std::cmp_less_equal(coord, std::numeric_limits<int16_t>::max()))
            {
                if (auto it = lookup.find(static_cast<int16_t>(coord));
                    it != lookup.end())
                {
                    return it->second;
                }
            }

            return {};
        };

        int dx = 0, dy = 1;
        int px = 0, py = 0;

        auto move = [](int dist, int& pos, std::span<const int16_t> obstacles)
        {
            // std::println("{}", obstacles);
            if (dist < 0)
            {
                auto range = std::views::reverse(obstacles);
                auto it =
                    std::ranges::upper_bound(range, pos, std::greater<>{});
                if (it == range.end())
                {
                    pos += dist;
                }
                else
                {
                    pos = std::max(*it + 1, pos + dist);
                }
            }
            else
            {
                auto it = std::ranges::upper_bound(obstacles, pos);
                if (it == obstacles.end())
                {
                    pos += dist;
                }
                else
                {
                    pos = std::min(*it - 1, pos + dist);
                }
            }
        };

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
            assert(command > 0);
            if (dx)
            {
                move(command * dx, px, get_obstacles(py, obstacles_by_y));
            }
            else
            {
                move(command * dy, py, get_obstacles(px, obstacles_by_x));
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
