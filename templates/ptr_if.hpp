#include <bit>
#include <type_traits>

#include "int_if.hpp"

template <typename T>
    requires(std::is_pointer_v<T>)
[[nodiscard, gnu::always_inline]] constexpr T
ptrif(bool c, T a, std::type_identity_t<T> b) noexcept
{
    return std::bit_cast<T>(
        iif(c, std::bit_cast<std::size_t>(a), std::bit_cast<std::size_t>(b)));
}
