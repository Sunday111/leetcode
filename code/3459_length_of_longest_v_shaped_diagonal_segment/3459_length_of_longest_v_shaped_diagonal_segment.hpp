#pragma once

#include <algorithm>
#include <vector>

#include "force_inline.hpp"
#include "hot_path.hpp"
#include "integral_aliases.hpp"

struct Vec2
{
    i16 x{};
    i16 y{};

    FORCE_INLINE HOT_PATH constexpr Vec2& operator+=(
        const Vec2& another) noexcept
    {
        x += another.x;  // NOLINT
        y += another.y;  // NOLINT
        return *this;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr Vec2 operator+(
        const Vec2& another) const noexcept
    {
        auto cpy = *this;
        cpy += another;
        return cpy;
    }
};

class Solution
{
public:
    using Grid = std::vector<std::vector<int>>;

    static constexpr std::array<Vec2, 4> kDirections{{
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, -1},
    }};

    static constexpr std::array<int, 2> kSeq{2, 0};

    [[nodiscard]] FORCE_INLINE HOT_PATH static constexpr u16 longestSeqFrom(
        const Grid& grid,
        const Vec2& size,
        const Vec2& start,
        const Vec2& dir) noexcept
    {
        u8 seq_idx = cell(grid, start) == 2;
        u16 len = 0;
        auto pos = start + dir;
        while (isValid(pos, size) && cell(grid, pos) == kSeq[seq_idx])
        {
            seq_idx = !seq_idx;
            ++len;
            pos += dir;
        }

        return len;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH static constexpr u16 longestVFrom(
        const Grid& grid,
        const Vec2& size,
        const Vec2& start,
        const Vec2& first_dir,
        const Vec2& second_dir) noexcept
    {
        u16 max_length = 1, current_length = 1;
        auto corner = start + first_dir;
        u8 seq_idx = 0;
        while (isValid(corner, size) && cell(grid, corner) == kSeq[seq_idx])
        {
            ++current_length;
            u16 seq = longestSeqFrom(grid, size, corner, second_dir);
            max_length = std::max<u16>(current_length + seq, max_length);

            seq_idx = !seq_idx;
            corner += first_dir;
        }

        return max_length;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH static constexpr bool isValid(
        const Vec2& v,
        const Vec2& size) noexcept
    {
        return std::bit_cast<u16>(v.x) < std::bit_cast<u16>(size.x) &&
               std::bit_cast<u16>(v.y) < std::bit_cast<u16>(size.y);
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH static constexpr const int& cell(
        const Grid& grid,
        const Vec2& pos) noexcept
    {
        return grid[static_cast<u16>(pos.y)][static_cast<u16>(pos.x)];
    }

    [[nodiscard]] static constexpr int lenOfVDiagonal(const Grid& grid) noexcept
    {
        const Vec2 size{
            .x = static_cast<i16>(grid.front().size()),
            .y = static_cast<i16>(grid.size()),
        };

        u16 r = 0;

        for (Vec2 start{}; start.y != size.y; ++start.y)
        {
            for (start.x = 0; start.x != size.x; ++start.x)
            {
                if (cell(grid, start) != 1) continue;

                for (u8 i = 0; i != 4; ++i)
                {
                    r = std::max(
                        longestVFrom(
                            grid,
                            size,
                            start,
                            kDirections[i],
                            kDirections[(i + 1) % 4]),
                        r);
                }
            }
        }

        return r;
    }
};
