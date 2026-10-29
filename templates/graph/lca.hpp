#pragma once

#include <algorithm>
#include <concepts>
#include <type_traits>
#include <utility>

#include "min2.hpp"
#include "sparse_table/st_make.hpp"
#include "sparse_table/st_range.hpp"

// Expects a tree's Euler tour of (depth, vertex) pairs.
// Tour and buffer must not overlap; buffer needs
// st_required_buffer_size(length).
template <
    std::unsigned_integral Index,
    std::unsigned_integral Position,
    std::unsigned_integral Depth>
[[nodiscard, gnu::always_inline]] constexpr SparseTable<
    std::pair<Depth, Index>,
    Position,
    decltype(min2)>
lca_preprocess(
    const std::pair<Depth, Index>* tour,
    Position length,
    std::pair<Depth, Index>* buffer) noexcept
{
    return st_make<std::pair<Depth, Index>, Position, decltype(min2)>(
        tour,
        length,
        buffer);
}

// u and v are vertex indices; first must belong to the tour used by table.
template <
    std::unsigned_integral Index,
    std::unsigned_integral Position,
    std::unsigned_integral Depth>
[[nodiscard, gnu::always_inline]] constexpr Index lca(
    const SparseTable<std::pair<Depth, Index>, Position, decltype(min2)>& table,
    const Position* first,
    std::type_identity_t<Index> u,
    std::type_identity_t<Index> v) noexcept
{
    const Position begin = std::min(first[u], first[v]);
    const auto end = static_cast<Position>(std::max(first[u], first[v]) + 1);
    return st_range(table, begin, end).second;
}
