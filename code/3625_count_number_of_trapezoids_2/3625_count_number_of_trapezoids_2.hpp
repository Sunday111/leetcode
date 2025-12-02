#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "bump_hash_map.hpp"
#include "cast.hpp"
#include "force_inline.hpp"
#include "integral_aliases.hpp"

struct Line
{
    int A, B, C;
};

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
        return std::bit_cast<To>(cast<std::make_signed_t<To>>(v));
    }
    else
    {
        return cast<To>(v);
    }
}

struct MidInfo
{
    u32 num_points = 0;
    std::unordered_map<u64, u32> lines_to_cnt;
};

using SolutionStorage = GlobalBufferStorage<1 << 26>;

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

    struct Hasher
    {
        [[nodiscard]] FORCE_INLINE constexpr u64 operator()(
            u32 x) const noexcept
        {
            u64 z = x;
            z += 0x9e3779b97f4a7c15ULL;
            z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
            return z >> 32U;
        }

        [[nodiscard]] FORCE_INLINE constexpr u64 operator()(
            u64 x) const noexcept
        {
            u64 z = x + 0x9e3779b97f4a7c15ULL;
            z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
            z = (z ^ (z >> 31U));
            return z;
        }
    };

    u32 countTrapezoids(std::vector<std::vector<int>>& points) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();
        using SlopeInfo =
            ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage, Hasher>>;
        std::ranges::sort(points);
        ObjectWithoutDtor<BumpHashMap<u32, SlopeInfo, SolutionStorage, Hasher>>
            slope_to_info;
        slope_to_info->reserve(2 * points.size() * points.size());
        ObjectWithoutDtor<BumpHashMap<u64, MidInfo, SolutionStorage, Hasher>>
            mids;
        mids->reserve(2 * points.size() * points.size());
        for (size_t i = 0; i != points.size(); ++i)
        {
            const auto& pi = points[i];
            const int ix = pi[0], iy = pi[1];
            for (size_t j = i + 1; j != points.size(); ++j)
            {
                const auto& pj = points[j];
                const int jx = pj[0], jy = pj[1];

                auto& mid_info = mids.get()[pack_mid(ix, iy, jx, jy)];
                ++mid_info.num_points;
                const auto [a, b, c] = make_line(ix, iy, jx, jy);
                auto& si = slope_to_info.get()[pack_slope(a, b)].get();
                si.reserve(points.size());
                si[as<u32>(c)]++;
                ++mid_info.lines_to_cnt[pack_t(a, b, c)];
            }
        }

        u32 r = 0;
        for (auto& [slope, dist_to_cnt] : slope_to_info.get())
        {
            u32 s = 0;
            for (auto& [dist, f] : dist_to_cnt.get())
            {
                r += f * s;
                s += f;
            }
        }

        for (auto& [m, info] : mids.get())
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
