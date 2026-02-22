#pragma once

#include <algorithm>
#include <concepts>
#include <type_traits>

#include "force_inline.hpp"

template <std::integral T>
FORCE_INLINE constexpr void assign_max(T& a, std::type_identity_t<T> b) noexcept
{
    a = std::max(a, b);
}
