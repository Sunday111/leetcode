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
#include <unordered_set>
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

struct Line
{
    std::string_view parent;
    std::vector<std::string_view> children;
};

template <
    typename Key,
    typename Value,
    typename Hasher = std::hash<Key>,
    typename Cmp = std::equal_to<Key>,
    typename Allocator = std::allocator<std::pair<const Key, Value>>>
using Map = std::unordered_map<Key, Value, Hasher, Cmp, Allocator>;

template <
    typename Value,
    typename Hasher = std::hash<Value>,
    typename Cmp = std::equal_to<Value>,
    typename Allocator = std::allocator<Value>>
using Set = std::unordered_set<Value, Hasher, Cmp, Allocator>;

struct Figure
{
    constexpr Figure(const char* s)  // NOLINT
    {
        for (u8 y = 0; y != 3; ++y)
        {
            for (u8 x = 0; x != 3; ++x)
            {
                cells[y][x] = s[y * 3 + x] == '#';
            }
        }
    }

    [[nodiscard]] constexpr u32 popcount() const noexcept
    {
        u32 r{};
        for (auto& row : cells)
        {
            for (auto x : row) r += x;
        }
        return r;
    }

    std::array<std::array<bool, 3>, 3> cells;
};

using Request = std::array<u8, 8>;
