#include "int_if.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T negate_if(bool c, T v) noexcept
{
    return iif(c, -v, v);
}
