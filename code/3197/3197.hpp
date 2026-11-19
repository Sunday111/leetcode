#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

struct Rect
{
    u8 x_begin;
    u8 x_end;
    u8 y_begin;
    u8 y_end;

    [[nodiscard]] constexpr u8 w() const noexcept { return x_end - x_begin; }
    [[nodiscard]] constexpr u8 h() const noexcept { return y_end - y_begin; }
};

class Solution
{
public:
    [[nodiscard]] constexpr std::pair<Rect, Rect> splitX(
        const Rect& rect,
        u8 t) noexcept
    {
        auto r1 = rect, r2 = rect;
        r1.x_end = r2.x_begin = t + rect.x_begin;
        assert(t <= rect.w());
        return {r1, r2};
    }
    [[nodiscard]] constexpr std::pair<Rect, Rect> splitY(
        const Rect& rect,
        u8 t) noexcept
    {
        auto r1 = rect, r2 = rect;
        r1.y_end = r2.y_begin = t + rect.y_begin;
        assert(t <= rect.h());
        return {r1, r2};
    }

    [[nodiscard]] constexpr u32 findRectMinArea(
        const Rect& rect,
        const std::vector<std::vector<int>>& grid) noexcept
    {
        u8 min_x = rect.x_end - 1, min_y = rect.y_end - 1, max_x = rect.x_begin,
           max_y = rect.y_begin;

        bool any = false;
        for (u8 y = rect.y_begin; y != rect.y_end; ++y)
        {
            auto& row = grid[y];
            for (u8 x = rect.x_begin; x != rect.x_end; ++x)
            {
                if (row[x])
                {
                    min_x = std::min(min_x, x);
                    min_y = std::min(min_y, y);
                    max_x = std::max(max_x, x);
                    max_y = std::max(max_y, y);
                    any = true;
                }
            }
        }

        if (any)
        {
            return ((max_x - min_x) + 1) * ((max_y - min_y) + 1);
        }

        return ~u32{};
    }

    [[nodiscard]] constexpr u32 findTwoRectsWithMinArea(
        const Rect parent,
        const std::vector<std::vector<int>>& grid) noexcept
    {
        const u8 w = parent.w(), h = parent.h();

        u32 result = ~u32{};

        auto tryRects = [&](const std::pair<Rect, Rect>& rects)
        {
            auto area_1 = findRectMinArea(rects.first, grid);
            auto area_2 = findRectMinArea(rects.second, grid);
            if (area_1 != ~u32{} && area_2 != ~u32{})
            {
                result = std::min(result, area_1 + area_2);
            }
        };

        for (u8 t = 1; t != w; ++t) tryRects(splitX(parent, t));
        for (u8 t = 1; t != h; ++t) tryRects(splitY(parent, t));

        return result;
    }

    [[nodiscard]] constexpr u32 minimumSum(
        const std::vector<std::vector<int>>& grid) noexcept
    {
        const u8 h = grid.size() & 0xFF, w = grid.front().size() & 0xFF;
        const Rect gridRect{
            .x_begin = 0,
            .x_end = w,
            .y_begin = 0,
            .y_end = h,
        };

        u32 result = ~u32{};

        auto tryRects = [&](const std::pair<Rect, Rect>& rects)
        {
            u32 firstRectMinArea = findRectMinArea(rects.first, grid);
            u32 secondRectMinArea = findRectMinArea(rects.second, grid);
            if (firstRectMinArea == ~u32{} || secondRectMinArea == ~u32{})
            {
                return;
            }

            if (auto twoRectsMinArea =
                    findTwoRectsWithMinArea(rects.first, grid);
                twoRectsMinArea != ~u32{})
            {
                result = std::min(twoRectsMinArea + secondRectMinArea, result);
            }

            if (auto twoRectsMinArea =
                    findTwoRectsWithMinArea(rects.second, grid);
                twoRectsMinArea != ~u32{})
            {
                result = std::min(twoRectsMinArea + firstRectMinArea, result);
            }
        };

        for (u8 t = 1; t != w; ++t)
        {
            tryRects(splitX(gridRect, t));
        }
        for (u8 t = 1; t != h; ++t)
        {
            tryRects(splitY(gridRect, t));
        }

        return result;
    }
};
