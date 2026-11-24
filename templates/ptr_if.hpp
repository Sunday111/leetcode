#pragma once

#include <cstdint>
#include <type_traits>

#include "int_if.hpp"

template <typename T>
    requires(std::is_pointer_v<T>)
[[nodiscard, gnu::always_inline]] constexpr T
ptrif(bool c, T a, std::type_identity_t<T> b) noexcept
{
    if consteval
    {
        return c ? a : b;
    }
    else
    {
        return reinterpret_cast<T>(
            iif(c,
                reinterpret_cast<std::uintptr_t>(a),
                reinterpret_cast<std::uintptr_t>(b)));
    }
}
