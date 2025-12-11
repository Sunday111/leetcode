#pragma once

#include <algorithm>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <print>
#include <ranges>
#include <span>
#include <thread>
#include <unordered_map>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "swap_if_greater.hpp"

using Clock = std::chrono::high_resolution_clock;

inline constexpr bool kDebugPrint = true;

template <typename... Args>
inline auto log(std::format_string<Args...> fmt, Args&&... args) noexcept
{
    if constexpr (kDebugPrint)
    {
        std::print(fmt, std::forward<Args>(args)...);
    }
}

template <typename... Args>
inline auto logln(std::format_string<Args...> fmt, Args&&... args) noexcept
{
    if constexpr (kDebugPrint)
    {
        std::println(fmt, std::forward<Args>(args)...);
    }
}

namespace stdr = std::ranges;
namespace stdv = std::views;
