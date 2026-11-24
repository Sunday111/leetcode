#pragma once

#include "ptr_if.hpp"

inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return *ptrif(a < b, &b, &a);
};
