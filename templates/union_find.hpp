#pragma once

#include <utility>

#include "force_inline.hpp"

template <typename T>
class UnionFind
{
public:
    struct Node
    {
        T size;
        T parent;
    };

    FORCE_INLINE constexpr UnionFind(Node* buffer, T size) noexcept
        : nodes(buffer)
    {
        for (T x = 0; x != size; ++x) nodes[x] = {.size = 1, .parent = x};
    }

    [[nodiscard]] FORCE_INLINE constexpr T find(T x) noexcept
    {
        // Path halving
        while (nodes[x].parent != x)
        {
            T& p = nodes[x].parent;
            x = p = nodes[p].parent;
        }
        return x;
    }

    // Returns true if subgraphs have been merged
    FORCE_INLINE constexpr bool merge(T x, T y) noexcept
    {
        // Union by size
        x = find(x);
        y = find(y);

        if (x != y)
        {
            if (nodes[x].size < nodes[y].size) std::swap(x, y);
            nodes[y].parent = x;
            nodes[x].size += nodes[y].size;
        }

        return x != y;
    }

    Node* nodes;
};
