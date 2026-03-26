#include <algorithm>
#include <cstdint>
#include <ranges>
#include <vector>

// https://leetcode.com/problems/equal-sum-grid-partition-ii/




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;


namespace stdr = std::ranges;
namespace stdv = std::views;

class Solution
{
public:
    template <typename T, typename Getter>
    [[nodiscard]] static constexpr bool solve_2d(
        u32* right,
        u32* left,
        const T total,
        const u32 max_val,
        const u32 h,
        const u32 w,
        Getter&& get) noexcept
    {
        auto test = [&max_val] [[nodiscard, gnu::always_inline]] (
                        const auto& m,
                        T v,
                        bool corner) noexcept
        {
            // when value is greater than maximum value found in the grid
            // the index becomes zero, whose frequency is always zero
            return m[v & -T{v <= max_val}] > !corner;
        };

        T s = 0;

        auto add_column = [&] [[gnu::always_inline]] (u32 x) noexcept
        {
            for (u32 y = 0; y != h; ++y)
            {
                u32 v = get(y, x);
                right[v]--;
                left[v]++;
                s += v;
            }
        };

        {
            add_column(0);
            T s2 = total - s;
            T d = std::max(s, s2) - std::min(s, s2);
            bool c1 = get(0, 0) == d || get(h - 1, 0) == d;
            bool c2 = ((w != 2) || (get(0, 1) == d || get(h - 1, 1) == d));
            if (s == s2) return true;
            if (s > s2 && test(left, d, c1)) return true;
            if (s2 > s && test(right, d, c2)) return true;
        }

        for (u32 x : stdv::iota(u32{0}, w) | stdv::drop(1) |
                         stdv::take(w - std::min(w, 3u)))
        {
            add_column(x);
            auto s2 = total - s;
            if (s == s2) return true;
            if (s > s2 && test(left, s - s2, true)) return true;
            if (s2 > s && test(right, s2 - s, true)) return true;
        }

        if (w != 2)
        {
            add_column(w - 2);

            auto s2 = total - s;
            T d = std::max(s, s2) - std::min(s, s2);
            bool c2 = (get(0, w - 1) == d || get(h - 1, w - 1) == d);
            if (s == s2) return true;
            if (s > s2 && test(left, d, true)) return true;
            if (s2 > s && test(right, d, c2)) return true;
        }

        // when this function returns false
        // it guarantees that left array is full and right array is empty
        // so this call is necessary
        add_column(w - 1);

        return false;
    }

    template <typename T>
    [[nodiscard, gnu::always_inline]] static constexpr bool canPartitionImpl(
        const std::vector<std::vector<u32>>& g,
        const u32 w,
        const u32 h,
        u32* full,
        u32* empty) noexcept
    {
        if (h == 1 && w == 1) return false;

        if (h == 1 || w == 1)
        {
            auto rng = g | stdv::join;
            T total = stdr::fold_left(rng, T{}, std::plus{});
            T s{}, a = total - g[h - 1][w - 1], b = total + g[0][0];
            for (auto v : rng)
            {
                s += v;
                if (2 * s == total) return true;
                if (2 * s == total + v) return true;
                if (2 * s == a) return true;
                if (2 * s == b) return true;
            }
            return false;
        }

        T total{};
        u32 max_val = 0;

        for (auto v : g | stdv::join)
        {
            total += v;
            max_val = std::max(max_val, v);
        }

        for (auto v : g | stdv::join)
        {
            ++full[v];
        }

        auto get_xy = [&g] [[gnu::always_inline]] (u32 y, u32 x) -> u32
        {
            return g[x][y];
        };

        auto get_yx = [&g] [[gnu::always_inline]] (u32 y, u32 x) -> u32
        {
            return g[y][x];
        };

        // First try horizontal splits and then vertical splits
        bool r = solve_2d(full, empty, total, max_val, h, w, get_yx) ||
                 solve_2d(empty, full, total, max_val, w, h, get_xy);
        // only clean empty array if result is true
        std::fill_n(empty, (max_val + 1) & -u32{r}, 0);
        std::fill_n(full, max_val + 1, 0);
        return r;
    }

    [[nodiscard]] bool canPartitionGrid(
        const std::vector<std::vector<int>>& orig) noexcept
    {
        u32 h = static_cast<u32>(orig.size());
        u32 w = static_cast<u32>(orig[0].size());
        auto& g = reinterpret_cast<const std::vector<std::vector<u32>>&>(orig);
        static u32 full[100'001], empty[100'001];

        if (w * h < 42000) return canPartitionImpl<u32>(g, w, h, full, empty);
        return canPartitionImpl<u64>(g, w, h, full, empty);
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
