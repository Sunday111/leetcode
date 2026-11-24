#pragma once

#include <type_traits>

#include "minmax/max2.hpp"
#include "minmax/ref/max2_ref.hpp"
#include "upd.hpp"

inline static constexpr auto upd_max =
    []<typename T> [[gnu::always_inline]] (
        T& x,
        const std::type_identity_t<T>& another) noexcept -> T&
{
    if constexpr (std::is_scalar_v<T>)
        return upd(x, another, max2);
    else
        return upd(x, another, max2_ref);
};
