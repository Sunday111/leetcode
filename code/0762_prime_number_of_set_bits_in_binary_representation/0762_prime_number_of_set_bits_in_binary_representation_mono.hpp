#include <immintrin.h>
#include <xmmintrin.h>

#include <array>
#include <bit>
#include <concepts>
#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

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

#define WITH_BMI2 __attribute__((__target__("bmi2")))

// Returns value >= v such that popcount(value) == x
[[nodiscard]] FORCE_INLINE WITH_BMI2 u32
next_with_x_popcount(u32 v, u8 x) noexcept
{
    u32 vp = std::popcount(v) & 0xFF;
    if (vp == x) return v;

    if (vp < x)
    {
        u32 need = x - vp;
        u32 add = _pdep_u32((1u << need) - 1, ~v);
        return v | add;
    }

    u32 dense = _pext_u32(v, ~u32{});
    dense = _pext_u32(~u32{}, v);
    dense &= ~((1u << (vp - x)) - 1);
    u32 tmp = _pdep_u32(dense, v);
    if (tmp >= v) return tmp;
    return next_with_same_popcount(tmp);
}

class Solution
{
public:
    inline static constexpr std::array<u8, 8>
        kPrimes{2, 3, 5, 7, 11, 13, 17, 19};

    [[nodiscard]] WITH_BMI2 static constexpr u32 countPrimeSetBits(
        u32 left,
        u32 right) noexcept
    {
        u32 r = 0;
        for (auto p : kPrimes)
        {
            auto x = next_with_x_popcount(left, p);
            while (x <= right)
            {
                ++r;
                x = next_with_same_popcount(x);
            }
        }

        return r;
    }
};
