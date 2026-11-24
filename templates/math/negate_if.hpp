#include "int_if.hpp"

template <std::integral T>
[[nodiscard, gnu::always_inline, gnu::hot]] inline constexpr T negate_if(
    bool c,
    T v) noexcept
{
    return iif(c, -v, v);
}
