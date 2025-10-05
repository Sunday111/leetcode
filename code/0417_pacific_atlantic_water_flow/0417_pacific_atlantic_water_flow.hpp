#pragma once

#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

struct Vec2
{
    u8 x, y;
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
        const Vec2 size{
            to<u8>(hmap[0].size()),
            to<u8>(hmap.size()),
        };

        const Vec2 lim{to<u8>(size.x - 1), to<u8>(size.y - 1)};

        constexpr u8 kPacific = 0b01;
        constexpr u8 kAtlantic = 0b10;
        constexpr u8 kBoth = kPacific | kAtlantic;
        static std::array<u8, 0xFFFF> bits;
        std::ranges::fill_n(bits.begin(), toIdx(size), 0);
        static std::array<Vec2, 21000> q;
        u32 qs = 0;

        // Vertical borders
        for (u8 x = 0; x != size.x; ++x)
        {
            Vec2 p{.x = x, .y = 0};
            q[qs++] = p;
            bits[toIdx(p)] |= kPacific;
            p.y = lim.y;
            q[qs++] = p;
            bits[toIdx(p)] |= kAtlantic;
        }

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
            u16 pi = toIdx(p);

            Vec2 left, right, bottom, top;  // NOLINT
            int h = hmap[p.y][p.x];

            auto test = [&](const Vec2& n)
            {
                if (n.x < size.x && n.y < size.y)
                {
                    const u16 ni = toIdx(n);
                    const u8 merged = bits[ni] | bits[pi];
                    bool cond = merged != bits[ni] && hmap[n.y][n.x] >= h;
                    bits[ni] = cond ? merged : bits[ni];
                    q[qs] = n;
                    qs += cond;
                }
            };

            left = p, --left.x, test(left);
            right = p, ++right.x, test(right);
            bottom = p, --bottom.y, test(bottom);
            top = p, ++top.y, test(top);
        }

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
