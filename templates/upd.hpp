#pragma once

#include <utility>

inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) -> T&
{
    return x = std::forward<F>(f)(x, another);
};
