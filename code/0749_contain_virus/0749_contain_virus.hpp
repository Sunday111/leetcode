#pragma once

#include <bitset>
#include <cassert>
#include <unordered_set>
#include <vector>

[[nodiscard]] constexpr uint16_t cast(std::integral auto v)
{
    return static_cast<uint16_t>(v);
}

struct Point
{
    [[nodiscard]] constexpr uint16_t pack() const
    {
        return ((x << 6) | y) & 0xFFFF;
    }

    template <typename F>
    constexpr void neighbors(uint16_t w, uint16_t h, F cb) const
    {
        if (x > 0) cb(Point{.x = cast(x - 1u), .y = y});
        if (x + 1 != w) cb(Point{.x = cast(x + 1u), .y = y});
        if (y > 0) cb(Point{.x = x, .y = cast(y - 1)});
        if (y + 1 != h) cb(Point{.x = x, .y = cast(y + 1)});
    }

    struct Hash
    {
        [[nodiscard]] constexpr size_t operator()(const Point& p) const
        {
            return std::hash<uint16_t>{}(p.pack());
        }
    };

    [[nodiscard]] constexpr bool operator==(const Point&) const = default;

    uint16_t x;
    uint16_t y;
};

class Solution
{
public:
    static constexpr uint8_t kHealty = 0;
    static constexpr uint8_t kInfected = 1;
    static constexpr uint8_t kSurrounded = 2;

    [[nodiscard]] static constexpr uint16_t containVirus(
        std::vector<std::vector<int>>& in_board)
    {
        const uint16_t h = static_cast<uint16_t>(in_board.size());
        const uint16_t w = static_cast<uint16_t>(in_board.front().size());

        std::vector<uint8_t> board;
        board.resize(w * h);

        // Create packed board
        {
            for (size_t y = 0; y != h; ++y)
            {
                auto& row = in_board[y];
                for (size_t x = 0; x != w; ++x)
                {
                    board[y * w + x] = static_cast<uint8_t>(row[x]);
                }
            }
        }

        auto get_cell = [&](const Point& p) -> uint8_t&
        {
            return board[p.y * w + p.x];
        };

        std::bitset<4096> visited{};
        std::vector<Point> queue;
        std::vector<std::unordered_set<Point, Point::Hash>> groups;
        groups.resize(10);
        for (auto& g : groups) g.reserve(50);

        std::unordered_set<uint16_t> surface_area;
        surface_area.reserve(128);

        uint16_t num_built_walls = 0;

        while (true)
        {
            visited = {};
            size_t next_group = 0;
            auto add_group = [&](const Point& start)
            {
                queue.clear();
                queue.push_back(start);

                if (next_group == groups.size()) groups.emplace_back();
                auto& group = groups[next_group++];
                group.clear();

                while (!queue.empty())
                {
                    auto p = queue.back();
                    queue.pop_back();

                    bool has_healthy_neighbors = false;
                    p.neighbors(
                        w,
                        h,
                        [&](const Point& neighbor)
                        {
                            auto neighbor_value = get_cell(neighbor);
                            if (neighbor_value == kHealty)
                            {
                                has_healthy_neighbors = true;
                                return;
                            }

                            if (const auto nm = neighbor.pack();
                                !visited[nm] && neighbor_value == kInfected)
                            {
                                queue.push_back(neighbor);
                                visited[nm] = true;
                            }
                        });

                    if (has_healthy_neighbors) group.insert(p);
                }

                if (group.empty()) --next_group;
            };

            // Group infected cells
            {
                Point p;  // NOLINT
                for (p.y = 0; p.y != h; ++p.y)
                {
                    for (p.x = 0; p.x != w; ++p.x)
                    {
                        if (auto m = p.pack();
                            !visited[m] && get_cell(p) == kInfected)
                        {
                            visited[m] = true;
                            add_group(p);
                        }
                    }
                }
            }

            // Identify the most dangerous group
            std::optional<std::pair<size_t, size_t>> most_dangerous_group;
            for (size_t group_index = 0; group_index != next_group;
                 ++group_index)
            {
                surface_area.clear();
                auto& group = groups[group_index];
                for (auto& point : group)
                {
                    point.neighbors(
                        w,
                        h,
                        [&](const Point& neighbor)
                        {
                            if (get_cell(neighbor) == kHealty)
                            {
                                surface_area.insert(neighbor.pack());
                            }
                        });
                }

                if (!surface_area.empty() &&
                    (!most_dangerous_group ||
                     surface_area.size() > most_dangerous_group->second))
                {
                    most_dangerous_group =
                        std::make_pair(group_index, surface_area.size());
                }
            }

            if (!most_dangerous_group) break;

            // Build walls around the most dangerous group
            for (const Point& p : groups[most_dangerous_group->first])
            {
                get_cell(p) = kSurrounded;
                p.neighbors(
                    w,
                    h,
                    [&](const Point& neighbor)
                    {
                        if (get_cell(neighbor) == kHealty)
                        {
                            ++num_built_walls;
                        }
                    });
            }

            // Remove the most dangerous group
            swap(groups[--next_group], groups[most_dangerous_group->first]);

            // Spread the from remaining groups of cells
            for (size_t group_index = 0; group_index != next_group;
                 ++group_index)
            {
                for (const auto& p : groups[group_index])
                {
                    p.neighbors(
                        w,
                        h,
                        [&](const Point& neighbor)
                        {
                            auto& v = get_cell(neighbor);
                            if (v == kHealty)
                            {
                                v = kInfected;
                            }
                        });
                }
            }
        }

        return num_built_walls;
    }
};
