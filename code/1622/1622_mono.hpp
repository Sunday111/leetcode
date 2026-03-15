#include <array>
#include <concepts>
#include <cstdint>
#include <utility>







#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

#define HOT_PATH __attribute__((hot))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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
        value += kMOD & -u32{value < rhs.value};
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
        value = cast<u32>(v);
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

    template <std::unsigned_integral Exp>
    [[nodiscard]] FORCE_INLINE constexpr ModInt pow(
        Exp exp) const noexcept HOT_PATH
    {
        ModInt r{1}, b = *this;

        while (exp)
        {
            // these two lines are equal to if (exp & 1) r *= b;
            u32 t = -(exp & 1);
            r *= ModInt((b.value & t) + (1u & ~t));

            b *= b;
            exp >>= 1;
        }

        return r;
    }

    u32 value = 0;
};

class Fancy
{
    inline static ModInt nums[100000], mul{1}, add{0}, inv_mul{1};
    u32 n = 0;

public:
    inline static constexpr auto kPow = []
    {
        std::array<ModInt, 101> r;

        for (ModInt base{0}; base.value != r.size(); ++base.value)
        {
            r[base.value] = base.pow(kMOD - 2);
        }

        return r;
    }();

    void append(int v) noexcept
    {
        nums[n++] = (ModInt{static_cast<u32>(v)} - add) * inv_mul;
    }

    void addAll(int v) noexcept { add += {static_cast<u32>(v)}; }

    void multAll(int v) noexcept
    {
        ModInt x{static_cast<u32>(v)};
        mul *= x, add *= x;
        inv_mul *= kPow[x.value];
    }

    [[nodiscard]] int getIndex(int idx) const noexcept
    {
        u32 m = -u32{std::cmp_less(idx, n)};
        return static_cast<int>(((nums[idx] * mul + add).value + 1) & m) - 1;
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
