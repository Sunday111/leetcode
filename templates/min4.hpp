#include "min2.hpp"

inline static constexpr auto min4 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c,
        const T& d) noexcept -> const T&
{
    return min2(min2(a, b), min2(c, d));
};
