#include "max2.hpp"

inline static constexpr auto max4 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c,
        const T& d) noexcept -> const T&
{
    return max2(max2(a, b), max2(c, d));
};
