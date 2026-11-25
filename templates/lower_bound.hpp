#pragma once

#include <concepts>
#include <type_traits>

// First integer in [first, last) satisfying a false-then-true predicate, or
// last.
template <std::integral T, typename Predicate>
    requires(!std::same_as<T, bool>)
[[nodiscard]] constexpr T
lower_bound(T first, T last, Predicate&& predicate) noexcept(
    noexcept(static_cast<bool>(predicate(first))))
{
    using U = std::make_unsigned_t<T>;
    while (first != last)
    {
        const U distance =
            static_cast<U>(static_cast<U>(last) - static_cast<U>(first));
        const T mid = static_cast<T>(first + static_cast<T>(distance / 2));
        if (predicate(mid))
        {
            last = mid;
        }
        else
        {
            first = static_cast<T>(mid + 1);
        }
    }
    return first;
}
