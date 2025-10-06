#include <algorithm>
#include <array>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

struct Vec2
{
    u8 x, y;

    [[nodiscard]] FORCE_INLINE constexpr bool operator==(
        const Vec2&) const noexcept = default;

    [[nodiscard]] FORCE_INLINE constexpr Vec2 left() const noexcept
    {
        auto copy = *this;
        --copy.x;
        return copy;
    }

    [[nodiscard]] FORCE_INLINE constexpr Vec2 right() const noexcept
    {
        auto copy = *this;
        ++copy.x;
        return copy;
    }

    [[nodiscard]] FORCE_INLINE constexpr Vec2 bottom() const noexcept
    {
        auto copy = *this;
        --copy.y;
        return copy;
    }

    [[nodiscard]] FORCE_INLINE constexpr Vec2 top() const noexcept
    {
        auto copy = *this;
        ++copy.y;
        return copy;
    }

    [[nodiscard]] FORCE_INLINE constexpr u16 toIdx() const noexcept
    {
        return to<u16>(y * 50 + x);
    }

    [[nodiscard]] FORCE_INLINE constexpr bool isValid(
        const Vec2& size) const noexcept
    {
        return x < size.x && y < size.y;
    }
};

class Solution
{
public:
    int swimInWater(std::vector<std::vector<int>>& grid) noexcept
    {
        // Size of the pool
        const Vec2 size{to<u8>(grid[0].size()), to<u8>(grid.size())};
        // Maximum coordinate within the pool
        const Vec2 target{to<u8>(size.x - 1), to<u8>(size.y - 1)};

        // first: water level
        // second: coordinate within the pool
        using Entry = std::pair<int, Vec2>;
        static std::array<Entry, 3000> q;
        u16 qs = 0;

        q[qs++] = {0, {0, 0}};

        auto heapOp = [&]<typename Op>(Op&& op)
        {
            std::forward<Op>(op)(
                std::begin(q),
                std::next(std::begin(q), qs),
                std::greater{},
                [](const Entry& e)
                {
                    auto& [l, p] = e;
                    u32 t = l & 0xFFFF;
                    t <<= 16;
                    t |= p.toIdx();
                    return t;
                });
        };

        static std::array<u8, 2501> visited;  // NOLINT
        std::ranges::fill_n(std::begin(visited), target.toIdx() + 1, 0);

        while (true)
        {
            heapOp(std::ranges::pop_heap);
            auto [level, p] = q[--qs];

            if (visited[p.toIdx()]) continue;
            visited[p.toIdx()] = 1;

            level = std::max(level, grid[p.y][p.x]);

            if (p == target) return level;

            auto test = [&](Vec2 n)
            {
                if (n.isValid(size) && !visited[n.toIdx()])
                {
                    q[qs++] = {level, n};
                    heapOp(std::ranges::push_heap);
                }
            };

            test(p.left());
            test(p.right());
            test(p.bottom());
            test(p.top());
        }

        std::unreachable();
    }
};
