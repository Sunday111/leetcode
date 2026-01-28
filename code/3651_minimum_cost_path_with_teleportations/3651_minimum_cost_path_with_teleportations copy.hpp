#include <algorithm>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

struct Vec2
{
    // NOLINTNEXTLINE
    FORCE_INLINE constexpr Vec2(u8 fill) noexcept : x{fill}, y{fill} {}
    FORCE_INLINE constexpr Vec2(u8 X, u8 Y) noexcept : x{X}, y{Y} {}

    u8 x, y;
};

[[nodiscard]] FORCE_INLINE constexpr Vec2 operator+(Vec2 a, Vec2 b) noexcept
{
    return {cast<u8>(a.x + b.x), cast<u8>(a.y + b.y)};
}

[[nodiscard]] FORCE_INLINE constexpr Vec2 operator-(Vec2 a, Vec2 b) noexcept
{
    return {cast<u8>(a.x - b.x), cast<u8>(a.y - b.y)};
}

class Solution
{
public:
    [[nodiscard]] static constexpr u32 minCost(
        std::vector<std::vector<u32>>& grid,
        u32 k) noexcept
    {
        const Vec2 size{cast<u8>(grid[0].size()), cast<u8>(grid.size())},
            origin = Vec2{0}, target = size - 1;
        std::vector<Vec2> sorted_coords;
        sorted_coords.reserve(grid.size() * grid[0].size());
        for (u8 y = 0; y != size.y; ++y)
        {
            for (u8 x = 0; x != size.x; ++x)
            {
                sorted_coords.emplace_back(Vec2{x, y});
            }
        }

        constexpr u32 kHuge = 100'000'000;
        grid.resize(size.y + 1);
        for (auto& row : grid) row.resize(size.x + 1, kHuge);

        u32 dp[81][81];
        for (u32 x = 0; x <= size.x; ++x) dp[size.y][x] = kHuge;
        for (u32 y = 0; y <= size.y; ++y) dp[size.x][y] = kHuge;

        auto weight_at = [&](Vec2 p) INLINE_LAMBDA -> const u32&
        {
            return grid[p.y][p.x];
        };

        auto dp_at = [&](Vec2 p) INLINE_LAMBDA -> u32&
        {
            return dp[p.y][p.x];
        };

        std::ranges::sort(sorted_coords, std::less{}, weight_at);
        constexpr Vec2 right{1, 0}, left{0xFF, 0}, bottom{0, 1};

        auto update_dp = [&](Vec2 p, u32 v) INLINE_LAMBDA
        {
            dp_at(p) = v;

            // same row as p.y
            for (Vec2 t = p + left; t.x != 0xFF; --t.x)
            {
                dp_at(t) = std::min(
                    dp_at(t + right) + weight_at(t + right),
                    dp_at(t + bottom) + weight_at(t + bottom));
            }

            while (--p.y != 0xFF)
            {
                for (Vec2 t = p; t.x != 0xFF; --t.x)
                {
                    dp_at(t) = std::min(
                        dp_at(t + right) + weight_at(t + right),
                        dp_at(t + bottom) + weight_at(t + bottom));
                }
            }
        };

        update_dp(target, 0);

        for

            return dp_at(origin);
    }

    [[nodiscard]] u32 minCost(
        const std::vector<std::vector<int>>& grid,
        u32 k) noexcept
    {
        return minCost(
            reinterpret_cast<const std::vector<std::vector<u32>>&>(grid),
            k);
    }
};
