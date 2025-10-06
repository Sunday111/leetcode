#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

struct Vec2
{
    u8 x, y;

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
};

class Solution
{
public:
    template <typename To>
    [[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
    {
        return static_cast<To>(v);
    }

    [[nodiscard]] FORCE_INLINE constexpr static u16 toIdx(
        const Vec2& v) noexcept
    {
        return to<u16>((u16{v.x} << 8) | v.y);
    }

    [[nodiscard]] static std::vector<std::vector<int>> pacificAtlantic(
        std::vector<std::vector<int>>& hmap) noexcept
    {
        // Size of the island
        const Vec2 size{to<u8>(hmap[0].size()), to<u8>(hmap.size())};
        // Maximum point coordinate within the island
        const Vec2 lim{to<u8>(size.x - 1), to<u8>(size.y - 1)};
        // Bit constants used in 'bits' array
        constexpr u8 kPacific = 1, kAtlantic = 2, kBoth = 3;
        // Static bits array
        static std::array<u8, 0xFFFF> bits;
        std::ranges::fill_n(bits.begin(), toIdx(size), 0);
        // Queue doesn't have to be cleaned as we do not read stale values
        static std::array<Vec2, 21000> q;
        u32 qs = 0;

        // Horizontal borders (parallel to x)
        for (u8 x = 0; x != size.x; ++x)
        {
            Vec2 p{.x = x, .y = 0};
            q[qs++] = p;
            bits[toIdx(p)] |= kPacific;
            p.y = lim.y;
            q[qs++] = p;
            bits[toIdx(p)] |= kAtlantic;
        }

        // Vertical borders (parallel to y)
        for (u8 y = 0; y != size.y; ++y)
        {
            Vec2 p{.x = 0, .y = y};
            q[qs++] = p;
            bits[toIdx(p)] |= kPacific;
            p.x = lim.x;
            q[qs++] = p;
            bits[toIdx(p)] |= kAtlantic;
        }

        while (qs)
        {
            Vec2 p = q[--qs];

            auto test = [&, pi = toIdx(p), h = hmap[p.y][p.x]](const Vec2& n)
            {
                // Note that if x or y were 0 and got decreased by 1, they would
                // become 0xFF (255), which is  greater than the maximum
                // possible size of an island, so checking < size is enough
                if (n.x < size.x && n.y < size.y)
                {
                    const u16 ni = toIdx(n);
                    const u8 merged = bits[ni] | bits[pi];
                    // Condition: neighbour cell is higher than source and
                    // merging their bits changes neighbour's bits
                    const bool cond = merged != bits[ni] && hmap[n.y][n.x] >= h;
                    bits[ni] = cond ? merged : bits[ni];
                    // Add to the queue if condition is true
                    // This looks weird but avoids extra branch.
                    q[qs] = n;
                    qs += cond;
                }
            };

            // Look at four neighbours
            test(p.left());
            test(p.right());
            test(p.bottom());
            test(p.top());
        }

        // Populate the result with points that have both bits
        std::vector<std::vector<int>> r;
        r.reserve(u16{size.x} * u16{size.y});
        for (u8 y = 0, t = 0; y != size.y; ++y)
        {
            for (u8 x = 0; x != size.x; ++x)
            {
                if (bits[toIdx({x, y})] == kBoth)
                {
                    std::vector<int> v;
                    // steal allocation from hmap
                    if (t != y)
                    {
                        v = std::move(hmap[t++]);
                        v.clear();
                    }
                    v.push_back(y);
                    v.push_back(x);
                    r.emplace_back(std::move(v));
                }
            }
        }

        return r;
    }
};
