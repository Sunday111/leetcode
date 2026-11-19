#pragma once

#include <bitset>
#include <vector>

struct Vec2
{
    int8_t x;
    int8_t y;

    [[nodiscard]] static constexpr Vec2 from_vector(
        const std::vector<int>& vec) noexcept
    {
        return Vec2{
            .x = static_cast<int8_t>(vec[0]),
            .y = static_cast<int8_t>(vec[1]),
        };
    }
    [[nodiscard]] constexpr std::vector<int> to_vector() const noexcept
    {
        return {x, y};
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        constexpr uint8_t mask = 0b111;
        return ((x & mask) == x) && ((y & mask) == y);
    }

    constexpr Vec2& operator+=(const Vec2& v) noexcept
    {
        x += v.x;  // NOLINT
        y += v.y;  // NOLINT
        return *this;
    }

    [[nodiscard]] constexpr uint8_t to_index() const noexcept
    {
        return static_cast<uint8_t>(y * 8 + x);
    }

    [[nodiscard]] constexpr bool operator==(const Vec2&) const noexcept =
        default;
};

class Solution
{
public:
    std::vector<std::vector<int>> queensAttacktheKing(
        std::vector<std::vector<int>>& in_queens,
        std::vector<int>& in_king)
    {
        std::bitset<64> queens;
        const auto king = Vec2::from_vector(in_king);

        for (auto& queen : in_queens)
        {
            auto p = Vec2::from_vector(queen);
            queens[p.to_index()] = 1;
        }

        constexpr std::array<Vec2, 8> directions{{
            {-1, -1},
            {1, -1},
            {-1, 1},
            {1, 1},
            {1, 0},
            {0, 1},
            {-1, 0},
            {0, -1},
        }};

        std::vector<std::vector<int>> result;
        result.reserve(6);

        for (Vec2 dir : directions)
        {
            Vec2 p = king;
            while (true)
            {
                p += dir;
                if (!p.is_valid()) break;
                if (queens[p.to_index()])
                {
                    result.push_back(p.to_vector());
                    break;
                }
            }
        }

        return result;
    }
};
