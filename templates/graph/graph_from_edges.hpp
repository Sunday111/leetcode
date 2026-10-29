#pragma once

#include <concepts>
#include <iterator>
#include <type_traits>

// Undirected edges use zero-based endpoints in [0, n).
// Degree and offset buffers must hold n elements, links 2 * m elements.
// Vertex counts, degrees and link counts must fit Index, Degree and Offset.
template <
    typename Edge,
    std::unsigned_integral Index,
    std::unsigned_integral Degree,
    std::unsigned_integral Offset>
[[gnu::always_inline]] constexpr void graph_from_edges(
    const Edge* edges,
    std::type_identity_t<Offset> m,
    Index n,
    Degree* degree,
    Offset* offset,
    Index* links) noexcept
{
    for (Index i = 0; i != n; ++i)
    {
        degree[i] = 0;
    }

    for (Offset i = 0; i != m; ++i)
    {
        const auto* edge = std::data(edges[i]);
        const auto a = static_cast<Index>(edge[0]);
        const auto b = static_cast<Index>(edge[1]);
        ++degree[a];
        ++degree[b];
    }

    Offset sum = 0;
    for (Index i = 0; i != n; ++i)
    {
        offset[i] = sum;
        sum = static_cast<Offset>(sum + degree[i]);
        degree[i] = 0;
    }

    for (Offset i = 0; i != m; ++i)
    {
        const auto* edge = std::data(edges[i]);
        const auto a = static_cast<Index>(edge[0]);
        const auto b = static_cast<Index>(edge[1]);
        links[offset[a] + degree[a]++] = b;
        links[offset[b] + degree[b]++] = a;
    }
}
