#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>






template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};

class Solution
{
    using u32 = uint32_t;
    using u64 = uint64_t;

public:
    constexpr u64 sumAndMultiply(u32 n) noexcept
    {
        u64 m = 1, x = 0, s = 0;
        while (n)
        {
            u32 d = n % 10;
            x += m * d;
            m *= iif(d, 10u, 1u);
            s += d;
            n /= 10;
        }

        return x * s;
    }
};
