#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

[[nodiscard, gnu::always_inline]] constexpr std::size_t
euler_tour_required_buffer_size(std::size_t n) noexcept
{
    return n == 0 ? 0 : n + (n - 1);
}

// Expects an undirected tree with vertices in [0, n) and root < n when n != 0.
// Tour needs euler_tour_required_buffer_size(n) elements; depth, first and
// each scratch array need n. Depth must hold n - 1; Position must hold the
// tour length. Records (depth, vertex) pairs on entry and after returning from
// each child, in link order.
template <
    std::unsigned_integral Index,
    std::unsigned_integral Degree,
    std::unsigned_integral Offset,
    std::unsigned_integral Depth,
    std::unsigned_integral Position>
[[gnu::always_inline]] constexpr void euler_tour(
    Index n,
    std::type_identity_t<Index> root,
    const Degree* degree,
    const Offset* offset,
    const Index* links,
    std::pair<Depth, Index>* tour,
    Depth* depth,
    Position* first,
    Index* stack,
    Degree* next_link) noexcept
{
    if (n == 0) return;

    std::size_t stack_size = 1;
    std::size_t tour_size = 0;
    stack[0] = root;
    next_link[0] = 0;
    depth[root] = 0;
    first[root] = 0;
    tour[tour_size++] = {0, root};

    while (stack_size != 0)
    {
        const Index vertex = stack[stack_size - 1];
        auto& next = next_link[stack_size - 1];
        if (next == degree[vertex])
        {
            --stack_size;
            if (stack_size != 0)
            {
                const Index parent = stack[stack_size - 1];
                tour[tour_size++] = {depth[parent], parent};
            }
        }
        else
        {
            const Index child =
                links[static_cast<std::size_t>(offset[vertex]) + next++];
            if (stack_size != 1 && child == stack[stack_size - 2]) continue;

            stack[stack_size] = child;
            next_link[stack_size] = 0;
            depth[child] = static_cast<Depth>(stack_size);
            first[child] = static_cast<Position>(tour_size);
            ++stack_size;
            tour[tour_size++] = {depth[child], child};
        }
    }
}
