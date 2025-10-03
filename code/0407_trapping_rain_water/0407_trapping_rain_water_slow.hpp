
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using u16 = uint16_t;
    using u8 = uint8_t;

    template <typename To>
    [[nodiscard]] static constexpr To to(auto v) noexcept
    {
        return static_cast<To>(v);
    }

    struct Vec2
    {
        u8 x, y;

        [[nodiscard]] constexpr u16 toIdx() const noexcept
        {
            return to<u16>((u16{x} << 8) | y);
        }
    };

    struct Area
    {
        u16 h = 0;
        std::vector<Vec2> points;
    };

    [[nodiscard]] static constexpr u32 trapRainWater(
        std::vector<std::vector<int>>& hmap) noexcept
    {
        std::vector<Area> v1, v2;
        auto *areas = &v1, *next_areas = &v2;
        u32 num_areas = 1;
        u16 num_next_areas = 0;

        std::array<u16, 0xFFFF> heights;  // NOLINT

        const u16 w = to<u16>(hmap[0].size());
        // Fill the root area with all points
        {
            const u16 m = to<u16>(hmap.size()), a = w * m;
            auto& root = areas->emplace_back();
            root.points.reserve(a);
            for (u8 y = 0; y != m; ++y)
            {
                for (u8 x = 0; x != w; ++x)
                {
                    root.points.push_back({.x = x, .y = y});
                    auto height = to<u16>(hmap[y][x]);
                    heights[root.points.back().toIdx()] = height;
                    root.h = std::max(height, root.h);
                }
            }
        }

        std::vector<Vec2> q;
        Area tmp;

        std::array<u8, 0xFFFF> visited{};
        u8 vt = 0;
        u16 lim_y = (to<u16>(hmap.size())) - 1,
            lim_x = to<u16>(hmap[0].size()) - 1;
        u32 r = 0;
        while (num_areas)
        {
            ++vt;
            for (u16 ai = 0; ai != num_areas; ++ai)
            {
                auto& area = areas->operator[](ai);
                for (auto& root : area.points)
                {
                    if (const u16 ri = root.toIdx();
                        visited[ri] == vt || heights[ri] >= area.h)
                    {
                        continue;
                    }

                    tmp.points.clear(), tmp.h = 0;
                    q.clear();
                    q.push_back(root);
                    bool spill = false;
                    while (!q.empty())
                    {
                        const auto p = q.back();
                        q.pop_back();
                        u16 pi = p.toIdx();
                        if (visited[pi] == vt) continue;
                        visited[pi] = vt;
                        u16 ph = heights[pi];
                        if (ph >= area.h) continue;
                        tmp.points.push_back(p);
                        tmp.h = std::max(tmp.h, ph);

                        spill |= !p.x || !p.y || p.x == lim_x || p.y == lim_y;

                        // Look at neighbours
                        if (p.x != 0) q.emplace_back(p).x--;
                        if (p.x != lim_x) q.emplace_back(p).x++;
                        if (p.y != 0) q.emplace_back(p).y--;
                        if (p.y != lim_y) q.emplace_back(p).y++;
                    }

                    if (!tmp.points.empty())
                    {
                        if (!spill)
                        {
                            r += (area.h - tmp.h) * tmp.points.size();
                        }

                        if (num_next_areas == next_areas->size())
                        {
                            next_areas->emplace_back();
                        }

                        if (area.points.size() == tmp.points.size())
                        {
                            next_areas->operator[](num_next_areas++) =
                                std::move(area);
                            break;
                        }

                        next_areas->operator[](num_next_areas++) =
                            std::move(tmp);
                    }
                }

                tmp = std::move(area);
            }

            std::swap(areas, next_areas);
            num_areas = num_next_areas;
            num_next_areas = 0;
        }

        return r;
    }
};
