#include <bit>
#include <concepts>
#include <cstdint>
#include <format>
#include <string>
#include <vector>




#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

// This is safe for n < 68
[[nodiscard]] FORCE_INLINE constexpr u64 ncr(u8 n, u8 r) noexcept
{
    if (r > n) return 0;
    if (r > n - r) r = n - r;

    u64 res = 1;
    for (u32 i = 1, k = n - r + i; i <= r; ++i, ++k)
    {
        res *= k;
        res /= i;
    }
    return res;
}



/* This is an implementation of Gosper's hack, which is an efficient method of
 * computing the next higher integer with the same number of set bits (popcout,
 * hamming weight)
 */
template <std::unsigned_integral T>
[[nodiscard]] FORCE_INLINE constexpr T next_with_same_popcount(T q) noexcept
{
    T r = q & -q;
    T n = q + r;
    q = (((n ^ q) >> 2) >> std::countr_zero(q)) | n;
    return q;
}

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::string> readBinaryWatch(
        u8 k) noexcept
    {
        if (k == 0) return {"0:00"};
        if (k > 8) return {};

        std::vector<std::string> res;
        res.reserve(ncr(9, k));

        for (u16 q = ((u16{1} << k) - 1) & 0xFFFF; q < (1 << 10);
             q = next_with_same_popcount(q))
        {
            u8 hour = (q >> 6) & 0xFF, min = q & 63;
            if (hour < 12 && min < 60)
            {
                res.emplace_back(std::format("{}:{:02}", hour, min));
            }
        }

        return res;
    }
};
