#include <algorithm>
#include <array>
#include <bit>
#include <ranges>
#include <tuple>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    struct Interval
    {
        u32 begin;
        u32 end;

        constexpr auto iota() const noexcept
        {
            return std::views::iota(begin, end);
        }

        constexpr u32 max_shift(Interval other) const noexcept
        {
            return std::max(
                end - 1 - std::min(end - 1, other.begin),
                other.end - 1 - std::min(other.end - 1, begin));
        }

        constexpr Interval overlap_at(Interval other, u32 shift) const noexcept
        {
            const auto first =
                std::max(begin, other.begin - std::min(other.begin, shift));
            const auto last =
                std::min(end, other.end - std::min(other.end, shift));
            return {first, std::max(first, last)};
        }
    };

    [[gnu::always_inline]] static constexpr auto to_bitmap(
        const std::vector<std::vector<int>>& img) noexcept
    {
        std::array<u32, 30> rows{};
        u32 rw = 0;
        u32 rh = 0;

        auto row = rows.begin();
        u32 y = 0;
        for (const auto& src : img)
        {
            auto& dst = *row++;
            u32 x = 0;
            for (int pixel : src)
            {
                dst |= u32{pixel == 1} << x;
                ++x;
            }
            rw |= dst;
            rh |= u32{dst != 0} << y;
            ++y;
        }

        const u32 x_end = std::bit_width(rw) & 31;
        const u32 y_end = std::bit_width(rh) & 31;
        return std::tuple{
            rows,
            Interval{std::min<u32>(std::countr_zero(rw) & 31, x_end), x_end},
            Interval{std::min<u32>(std::countr_zero(rh) & 31, y_end), y_end}};
    }

    int largestOverlap(
        const std::vector<std::vector<int>>& img1,
        const std::vector<std::vector<int>>& img2)
    {
        const auto [a, ax, ay] = to_bitmap(img1);
        const auto [b, bx, by] = to_bitmap(img2);
        if (ax.begin == ax.end || bx.begin == bx.end)
        {
            return 0;
        }

        const auto max_dx = ax.max_shift(bx);
        const auto max_dy = ay.max_shift(by);

        int r = 0;
        for (u32 dy : Interval{0, max_dy + 1}.iota())
        {
            const auto ab = ay.overlap_at(by, dy);
            const auto ba = by.overlap_at(ay, dy);

            for (u32 dx : Interval{0, max_dx + 1}.iota())
            {
                int x1 = 0, x2 = 0;
                for (auto lhs = a.begin() + ab.begin, end = a.begin() + ab.end;
                     lhs != end;
                     ++lhs)
                {
                    const auto rhs = b.begin() + (lhs - a.begin()) + dy;
                    x1 += std::popcount(*lhs & (*rhs << dx));
                    x2 += std::popcount(*lhs & (*rhs >> dx));
                }
                r = std::max({r, x1, x2});
                x1 = 0, x2 = 0;
                for (auto lhs = b.begin() + ba.begin, end = b.begin() + ba.end;
                     lhs != end;
                     ++lhs)
                {
                    const auto rhs = a.begin() + (lhs - b.begin()) + dy;
                    x1 += std::popcount(*lhs & (*rhs << dx));
                    x2 += std::popcount(*lhs & (*rhs >> dx));
                }
                r = std::max({r, x1, x2});
            }
        }

        return r;
    }
};
