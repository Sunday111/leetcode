#pragma once

#include <algorithm>
#include <cassert>
#include <span>

template <size_t extent>
static constexpr size_t spanHash(std::span<const uint8_t, extent> s)
{
    size_t hash = 14695981039346656037ULL;
    for (uint8_t c : s)
    {
        hash = (hash ^ c) * 1099511628211ULL;
    }
    return hash;
}

inline static constexpr auto sorted = [](auto& groups) -> decltype(auto)
{
    std::ranges::for_each(groups, std::ranges::sort);
    std::ranges::sort(groups);
    return groups;
};

[[nodiscard]] constexpr inline uint32_t isqrt(uint32_t s) noexcept
{
    if (s <= 1) return s;

    uint32_t x0 = s / 2;
    uint32_t x1 = (x0 + s / x0) / 2;

    while (x1 < x0)
    {
        x0 = x1;
        x1 = (x0 + s / x0) / 2;
    }

    return x0;
}

template <std::integral To, std::integral From>
[[nodiscard]] static constexpr To cast(From from) noexcept
{
    if constexpr (sizeof(To) == sizeof(From))
    {
        return std::bit_cast<To>(from);
    }
    else
    {
        return static_cast<To>(from);
    }
}

// #pragma GCC optimize("O3")

// #define ATTRS __attribute__((no_sanitize("all")))
// __attribute__((always_inline))

// __attribute__((optimize("O3")))

// #ifdef __GNUC__
//     #define ATTR inline __attribute__((always_inline))
// #else
//     #define ATTR inline
// #endif
