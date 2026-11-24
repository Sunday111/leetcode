#pragma once

#include <type_traits>

#include "min2.hpp"
#include "upd.hpp"

inline static constexpr auto upd_min =
    []<typename T> [[gnu::always_inline]] (
        T& x,
        const std::type_identity_t<T>& another) noexcept -> T&
{
    return upd(x, another, min2);
};
