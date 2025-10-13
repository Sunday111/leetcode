#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

struct Line
{
    int A, B, C;
};

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

[[nodiscard]] FORCE_INLINE constexpr Line
make_line(int x1, int y1, int x2, int y2) noexcept
{
    int a = y2 - y1;
    int b = x1 - x2;
    int c = x2 * y1 - x1 * y2;

    if (int g = std::gcd(abs(a), std::gcd(abs(b), std::abs(c))); g)
    {
        a /= g, b /= g, c /= g;
    }

    if (a < 0 || (a == 0 && b < 0))
    {
        a = -a, b = -b, c = -c;
    }

    return {a, b, c};
}

template <std::unsigned_integral To, std::integral From>
[[nodiscard]] FORCE_INLINE To as(From v) noexcept
{
    if constexpr (std::is_signed_v<From>)
    {
        return std::bit_cast<To>(static_cast<std::make_signed_t<To>>(v));
    }
    else
    {
        return static_cast<To>(v);
    }
}

struct MidInfo
{
    int num_points = 0;
    std::unordered_map<u64, int> lines_to_cnt;
};

class Solution
{
public:
    [[nodiscard]] FORCE_INLINE static constexpr u32 pack_slope(
        int a,
        int b) noexcept
    {
        u32 slope = as<u16>(a);
        slope <<= 16;
        slope |= as<u16>(b);
        return slope;
    }

    [[nodiscard]] FORCE_INLINE static constexpr u64
    pack_mid(int x1, int y1, int x2, int y2) noexcept
    {
        u64 m = as<u32>(x1 + x2);
        m <<= 32;
        m |= as<u32>(y1 + y2);
        return m;
    }

    [[nodiscard]] FORCE_INLINE static constexpr u64
    pack_t(int a, int b, int c) noexcept
    {
        u64 t = as<u16>(a);
        t <<= 16;
        t |= as<u16>(b);
        t <<= 32;
        t |= as<u32>(c);
        return t;
    }

    [[nodiscard]] FORCE_INLINE static constexpr auto comb_2(
        std::integral auto n) noexcept
    {
        return (n * (n - 1)) / 2;
    }

    int countTrapezoids(std::vector<std::vector<int>>& points) noexcept
    {
        using SlopeInfo = std::unordered_map<int, int>;
        std::ranges::sort(points);
        std::unordered_map<u32, SlopeInfo> slope_to_info;
        std::unordered_map<u64, MidInfo> mids;
        for (size_t i = 0; i != points.size(); ++i)
        {
            const auto& pi = points[i];
            const int ix = pi[0], iy = pi[1];
            for (size_t j = i + 1; j != points.size(); ++j)
            {
                const auto& pj = points[j];
                const int jx = pj[0], jy = pj[1];

                auto& mid_info = mids[pack_mid(ix, iy, jx, jy)];
                ++mid_info.num_points;
                const auto [a, b, c] = make_line(ix, iy, jx, jy);
                slope_to_info[pack_slope(a, b)][c]++;
                ++mid_info.lines_to_cnt[pack_t(a, b, c)];
            }
        }

        int r = 0;
        for (auto& [slope, dist_to_cnt] : slope_to_info)
        {
            int s = 0;
            for (auto& [dist, f] : dist_to_cnt)
            {
                r += f * s;
                s += f;
            }
        }

        for (auto& [m, info] : mids)
        {
            r -= comb_2(info.num_points);
            for (auto& [k, cnt] : info.lines_to_cnt)
            {
                r += comb_2(cnt);
            }
        }
        return r;
    }
};
