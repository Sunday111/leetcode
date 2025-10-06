#include <algorithm>
#include <array>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u64 = uint64_t;
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
        return to<u16>((y << 7) | x);
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
    [[nodiscard]] FORCE_INLINE static constexpr u64 pack(
        int effort,
        Vec2 p) noexcept
    {
        u64 r{to<u32>(effort)};
        r <<= 7;
        r |= (~p.x) & 127;
        r <<= 7;
        r |= (~p.y) & 127;
        return r;
    }

    [[nodiscard]] FORCE_INLINE static constexpr std::tuple<int, Vec2> unpack(
        u64 e) noexcept
    {
        Vec2 p;  // NOLINT
        p.y = (~e) & 127;
        e >>= 7;
        p.x = (~e) & 127;
        e >>= 7;
        return {e, p};
    }

    int minimumEffortPath(std::vector<std::vector<int>>& grid) noexcept
    {
        const Vec2 size{to<u8>(grid[0].size()), to<u8>(grid.size())};
        const Vec2 target{to<u8>(size.x - 1), to<u8>(size.y - 1)};

        static std::array<u64, 10000> q;
        u16 qs = 0;

        auto heapOp = [&]<typename Op>(Op&& op)
        {
            std::forward<Op>(op)(
                std::begin(q),
                std::next(std::begin(q), qs),
                std::greater{});
        };

        static std::array<u8, Vec2{100, 100}.toIdx() + 1> visited;  // NOLINT
        std::ranges::fill_n(std::begin(visited), target.toIdx() + 1, 0);

        q[qs++] = pack(0, {0, 0});

        while (true)
        {
            heapOp(std::ranges::pop_heap);
            auto [effort, p] = unpack(q[--qs]);

            if (visited[p.toIdx()]) continue;
            visited[p.toIdx()] = 1;

            const int ph = grid[p.y][p.x];

            if (p == target) return effort;

            auto test = [&](Vec2 n)
            {
                if (n.isValid(size) && !visited[n.toIdx()])
                {
                    int nh = grid[n.y][n.x];
                    q[qs++] = pack(std::max(effort, std::abs(nh - ph)), n);
                    heapOp(std::ranges::push_heap);
                }
            };

            test(p.left());
            test(p.right());
            test(p.bottom());
            test(p.top());
        }
    }
};
