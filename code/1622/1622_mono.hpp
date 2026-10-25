#include <array>
#include <concepts>
#include <cstdint>
#include <utility>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

inline constexpr u32 kMOD = 1'000'000'007;

struct ModInt
{
    u32 value = 0;
};

[[gnu::always_inline]] constexpr ModInt& operator+=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    lhs.value += rhs.value;
    lhs.value -= kMOD & -u32{lhs.value >= kMOD};
    return lhs;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt operator+(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

[[gnu::always_inline]] constexpr ModInt& operator*=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    u64 v = rhs.value;
    v *= lhs.value;
    if (v >= kMOD) v %= kMOD;
    lhs.value = cast<u32>(v);
    return lhs;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

template <std::unsigned_integral Exp>
[[nodiscard, gnu::always_inline]] constexpr ModInt pow(
    ModInt b,
    Exp exp) noexcept
{
    ModInt r{1};

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

[[gnu::always_inline]] constexpr ModInt& operator-=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    lhs.value += kMOD & -u32{lhs.value < rhs.value};
    lhs.value -= rhs.value;
    return lhs;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt operator-(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

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
            r[base.value] = pow(base, kMOD - 2);
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

#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif
