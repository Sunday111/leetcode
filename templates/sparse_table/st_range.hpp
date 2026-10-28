#pragma once

#include <bit>
#include <concepts>
#include <cstddef>
#include <type_traits>

#include "st.hpp"

// Requires begin < end <= table.size.
// Returns the aggregate over [begin, end).
template <typename T, std::unsigned_integral Index, typename Op>
[[nodiscard, gnu::always_inline]] constexpr T st_range(
    const SparseTable<T, Index, Op>& table,
    std::type_identity_t<Index> begin,
    std::type_identity_t<Index> end) noexcept
{
    const auto level = std::bit_width(static_cast<Index>(end - begin)) - 1;
    const std::size_t width = std::size_t{1} << level;
    const std::size_t offset = static_cast<std::size_t>(level) * table.size;
    return static_cast<T>(
        Op{}(table.x[offset + begin], table.x[offset + end - width]));
}
