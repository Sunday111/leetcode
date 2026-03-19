#include <vector>

#include "integral_aliases.hpp"

// https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/

constexpr u32 kMaxW = 1024;
constexpr u32 kBias = kMaxW * kMaxW;

struct Meow
{
    u32 t : 31 = kBias;
    u32 f : 1 = 0;

    [[gnu::always_inline]] Meow& operator+=(const Meow& rhs) noexcept
    {
        f |= rhs.f;
        t += rhs.t - kBias;
        return *this;
    }

    // NOLINTNEXTLINE
    [[gnu::always_inline, nodiscard]] operator bool() const noexcept
    {
        return f & (t == kBias);
    }
};

class Solution
{
public:
    u32 numberOfSubmatrices(const std::vector<std::vector<char>>& orig) noexcept
    {
        Meow g[kMaxW];

        const u16 w = static_cast<u16>(orig[0].size());
        std::fill_n(g, w, Meow{});

        u32 r = 0;

        for (auto& row : orig)
        {
            Meow s{};
            for (u16 x = 0; x != w; ++x)
            {
                auto& v = g[x];
                char c = row[x];
                bool is_x = c == 'X', is_y = c == 'Y';
                v += s += Meow{
                    .t = kBias + is_x - is_y,
                    .f = is_x || is_y,
                };
                r += !!v;
            }
        }

        return r;
    }
};

#include "sync_stdio.hpp"
