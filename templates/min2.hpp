#pragma once

#include "ptr_if.hpp"

inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return *ptrif(b < a, &b, &a);
};
