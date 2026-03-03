#include <algorithm>
#include <bit>
#include <concepts>
#include <cstdint>
#include <type_traits>




#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <std::integral T>
FORCE_INLINE constexpr void assign_max(T& a, std::type_identity_t<T> b) noexcept
{
    a = std::max(a, b);
}




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <std::unsigned_integral T>
[[nodiscard]] FORCE_INLINE static constexpr T clear_bit(T x, u8 i) noexcept
{
    return x & ~(T{1} << i);
}



template <std::unsigned_integral T>
    requires(sizeof(T) < 32)
[[nodiscard]] FORCE_INLINE constexpr u8 rightmost_one(T x) noexcept
{
    return std::countr_zero(x) & 0xFF;
}



// simplified std::exchange
template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard]] FORCE_INLINE constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}

class Solution
{
public:
    template <std::unsigned_integral T>
    [[nodiscard]] static constexpr u8 removeLastBit(T& x) noexcept
    {
        auto i = rightmost_one(x);
        x = clear_bit(x, i);
        return i;
    }

    [[nodiscard]] static constexpr u8 binaryGap(u32 n) noexcept
    {
        u8 r = 0, prev = removeLastBit(n);
        while (n)
        {
            auto curr = removeLastBit(n);
            assign_max(r, curr - exch(prev, curr));
        }
        return r;
    }
};
