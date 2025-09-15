#pragma once

#include <functional>

#include "overload.hpp"

inline constexpr auto mul = std::multiplies{};
inline constexpr auto plus = std::plus{};

template <typename T, size_t N>
[[nodiscard]] inline constexpr auto index_op(std::array<T, N>& arr) noexcept
{
    return [&]<typename Index>(Index&& index) -> T&
    {
        return arr[std::forward<Index>(index)];
    };
}

template <typename T, size_t N>
[[nodiscard]] inline constexpr auto index_op(
    const std::array<T, N>& arr) noexcept
{
    return [&]<typename Index>(Index&& index) -> const T&
    {
        return arr[std::forward<Index>(index)];
    };
}

template <typename T>
[[nodiscard]] inline constexpr auto index_op(std::vector<T>& arr) noexcept
{
    return [&]<typename Index>(Index&& index) -> T&
    {
        return arr[std::forward<Index>(index)];
    };
}

template <typename T>
[[nodiscard]] inline constexpr auto index_op(const std::vector<T>& arr) noexcept
{
    return [&]<typename Index>(Index&& index) -> const T&
    {
        return arr[std::forward<Index>(index)];
    };
}
