#include <bit>
#include <bitset>
#include <cstdint>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

#ifdef __GNUC__
#define HOT_PATH __attribute__((hot))
#else
#define FORCE_INLINE inline
#endif

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

inline constexpr u32 kMOD = 1'000'000'007;

struct ModInt
{
    FORCE_INLINE constexpr ModInt& operator+=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        value += rhs.value;
        if (value >= kMOD) value -= kMOD;
        return *this;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator+(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy += rhs;
        return copy;
    }

    FORCE_INLINE constexpr ModInt& operator-=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        value -= rhs.value;
        return *this;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator-(
        const ModInt& rhs) const noexcept HOT_PATH
    {
        auto copy = *this;
        copy -= rhs;
        return copy;
    }

    FORCE_INLINE constexpr ModInt& operator*=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        u64 v = rhs.value;
        v *= value;
        if (v >= kMOD) v %= kMOD;
        value = static_cast<u32>(v);
        return *this;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator*(
        const ModInt& rhs) const noexcept HOT_PATH
    {
        auto copy = *this;
        copy *= rhs;
        return copy;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt inverse()
        const noexcept HOT_PATH
    {
        auto a = value;
        u32 x0 = 1, x1 = 0, mod = kMOD;
        while (a)
        {
            u32 q = mod / a;
            u32 r = mod % a;
            u32 x2 = x1 - q * x0;
            mod = a;
            a = r;
            x1 = x0;
            x0 = x2;
        }
        return {(x1 + kMOD) % kMOD};
    }

    FORCE_INLINE constexpr ModInt& operator/=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        return *this *= rhs.inverse();
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator/(
        const ModInt& rhs) const noexcept HOT_PATH
    {
        auto copy = *this;
        copy /= rhs;
        return copy;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt pow(
        u32 exp) const noexcept HOT_PATH
    {
        if (exp == 0) return {1};
        std::bitset<32> bits(exp);
        ModInt ans = *this;
        u8 i = (31 - std::countl_zero(exp)) & 0xFF;
        while (i)
        {
            --i;
            ans *= ans;
            ans *= bits[i] ? *this : ModInt{1};
        }
        return ans;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt pow(
        u64 exp) const noexcept HOT_PATH
    {
        if (exp == 0) return {1};
        std::bitset<64> bits(exp);
        ModInt ans = *this;
        u8 i = (63 - std::countl_zero(exp)) & 0xFF;
        while (i)
        {
            --i;
            ans *= ans;
            ans *= bits[i] ? *this : ModInt{1};
        }
        return ans;
    }

    u32 value = 0;
};

class Solution
{
public:
    [[nodiscard]] static constexpr u32 countGoodNumbers(u64 n) noexcept
    {
        u64 odd = n / 2, even = n - odd;
        return (ModInt{4}.pow(odd) * ModInt{5}.pow(even)).value;
    }
};
