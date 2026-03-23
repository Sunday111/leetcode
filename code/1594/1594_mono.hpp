#include <algorithm>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;


inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::max(a, b);
};

inline static constexpr auto max4 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c,
        const T& d) noexcept -> const T&
{
    return max2(max2(a, b), max2(c, d));
};


inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::min(a, b);
};

inline static constexpr auto min4 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c,
        const T& d) noexcept -> const T&
{
    return min2(min2(a, b), min2(c, d));
};


namespace stdr = std::ranges;
namespace stdv = std::views;


using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
// https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/

class Solution
{
public:
    [[nodiscard]] constexpr i32 maxProductPath(
        const std::vector<std::vector<i32>>& grid) const noexcept
    {
        const u8 h = grid.size() & 0xFF, w = grid[0].size() & 0xFF;
        i64 dp_lo[16], dp_hi[16];

        // first row
        std::inclusive_scan(
            grid[0].begin(),
            grid[0].end(),
            dp_hi,
            std::multiplies{},
            i64{1});
        std::copy_n(dp_hi, w, dp_lo);

        for (u8 y = 1; y != h; ++y)
        {
            auto& row = grid[y];
            dp_hi[0] *= row[0];
            dp_lo[0] *= row[0];

            for (u8 x = 1; x != w; ++x)
            {
                i64 v = row[x];
                i64 a = dp_lo[x - 1] * v;
                i64 b = dp_lo[x] * v;
                i64 c = dp_hi[x - 1] * v;
                i64 d = dp_hi[x] * v;
                dp_hi[x] = max4(a, b, c, d);
                dp_lo[x] = min4(a, b, c, d);
            }
        }

        return static_cast<i32>(max2(dp_hi[w - 1], -1L) % 1'000'000'007);
    }
};
