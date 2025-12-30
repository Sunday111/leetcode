#include <algorithm>
#include <functional>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    static constexpr u8 numMagicSquaresInside(
        std::vector<std::vector<int>>& g) noexcept
    {
        u8 h = g.size() & 0xF, w = g[0].size() & 0xF, r = 0;

        for (u8 y0 = 0; y0 < h - 2; ++y0)
        {
            for (u8 x0 = 0; x0 < w - 2; ++x0)
            {
                std::array<u8, 8> sums{};
                u8 *sr = sums.data(), *sc = sr + 3, *sd = sc + 3;
                bool ok = true;

                u16 bits = 0;
                for (u8 dy = 0; dy != 3; ++dy)
                {
                    u8 y = y0 + dy;

                    // sum diagonals
                    sd[0] += g[y][x0 + dy];
                    sd[1] += g[y][x0 + 2 - dy];

                    for (u8 dx = 0; dx != 3; ++dx)
                    {
                        u8 x = x0 + dx;
                        u8 v = g[y][x] & 0xF;
                        // all values are distinct
                        ok = ok && !((1 << v) & bits);
                        bits |= (1 << v);

                        // sum rows
                        sr[dy] += v;

                        // sum columns
                        sc[dx] += v;
                    }
                }

                // all sums are equal
                ok &= std::ranges::all_of(
                    sums,
                    std::bind_front(std::equal_to{}, sums[0]));

                // Met only numbers in range [0,9]
                ok &= !(bits & ~u16{0b1111111110});

                r += ok;
            }
        }

        return r;
    }
};
