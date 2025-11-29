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
        return cast<u16>((y << 6) | x);
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
    [[nodiscard]] FORCE_INLINE static constexpr u32 pack(
        Vec2 p,
        u16 level) noexcept
    {
        u32 r{level};
        r <<= 6;
        r |= (~p.x) & 63;
        r <<= 6;
        r |= (~p.y) & 63;
        return r;
    }

    [[nodiscard]] FORCE_INLINE static constexpr std::pair<u16, Vec2> unpack(
        u32 e) noexcept
    {
        Vec2 p;  // NOLINT
        p.y = (~e) & 63;
        e >>= 6;
        p.x = (~e) & 63;
        e >>= 6;
        return {e & 0xFFFF, p};
    }

    u16 swimInWater(std::vector<std::vector<int>>& grid) noexcept
    {
        // Size of the pool
        const Vec2 size{cast<u8>(grid[0].size()), cast<u8>(grid.size())};
        // Maximum coordinate within the pool
        const Vec2 target{cast<u8>(size.x - 1), cast<u8>(size.y - 1)};

        static std::array<u32, 2500> q;
        u16 qs = 0;

        q[qs++] = pack({0, 0}, 0);

        auto heapOp = [&]<typename Op>(Op&& op)
        {
            std::forward<Op>(op)(
                std::begin(q),
                std::next(std::begin(q), qs),
                std::greater{});
        };

        static std::array<u8, Vec2{50, 50}.toIdx() + 1> visited;  // NOLINT
        std::ranges::fill_n(std::begin(visited), target.toIdx() + 1, 0);

        while (true)
        {
            heapOp(std::ranges::pop_heap);
            auto [level, p] = unpack(q[--qs]);

            if (visited[p.toIdx()]) continue;
            visited[p.toIdx()] = 1;

            level = std::max<u16>(level, grid[p.y][p.x] & 0xFFFF);

            if (p == target) return level;

            auto test = [&](Vec2 n)
            {
                if (n.isValid(size) && !visited[n.toIdx()])
                {
                    q[qs++] = pack(n, level);
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
