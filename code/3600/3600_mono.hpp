#include <algorithm>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;



#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

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




inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::min(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);

namespace stdr = std::ranges;

class Solution
{
public:
    [[nodiscard]] int impl(
        u32 n,
        const std::vector<std::vector<u32>>& edges,
        u32 k) const noexcept
    {
        using UF = UnionFind<u32>;
        using Node = typename UF::Node;

        static u32 edges_heap[100'001];

        static Node nodes[100'001];
        UF uf{nodes, n};
        u32 heap_size = 0;

        u32 min_edge = ~u32{};
        for (u32 i = 0; i != edges.size(); ++i)
        {
            auto& edge = edges[i];
            u32 u = edge[0], v = edge[1], s = edge[2], must = edge[3];
            if (must)
            {
                if (!uf.merge(u, v)) return -1;
                upd_min(min_edge, s);
            }
            else
            {
                edges_heap[heap_size++] = i;
            }
        }

        if (nodes[uf.find(0)].size != n)
        {
            constexpr auto cmp = std::less{};
            const auto proj =
                [&] [[nodiscard, gnu::always_inline]] (u32 i) noexcept -> u64
            {
                auto& edge = edges[i];
                u32 s = edge[2], must = edge[3];
                return s | (must << 20);
            };

            stdr::make_heap(edges_heap, edges_heap + heap_size, cmp, proj);

            auto vals_end = edges_heap + heap_size + 1;
            u32* vals = vals_end;

            while (heap_size && nodes[uf.find(0)].size != n)
            {
                auto& edge = edges[edges_heap[0]];
                u32 u = edge[0], v = edge[1], s = edge[2];

                if (uf.merge(u, v)) *(--vals) = s;

                stdr::pop_heap(edges_heap, edges_heap + heap_size--, cmp, proj);
            }

            u32 num_vals = static_cast<u32>(vals_end - vals);
            vals[0] <<= !!k;
            upd_min(min_edge, vals[0]);
            upd_min(min_edge, vals[k] | -u32{num_vals <= k});
        }

        if (nodes[uf.find(0)].size == n) return static_cast<int>(min_edge);

        return -1;
    }

    [[nodiscard]] int maxStability(
        int n,
        const std::vector<std::vector<int>>& edges,
        int k) const noexcept
    {
        return impl(
            static_cast<u32>(n),
            reinterpret_cast<const std::vector<std::vector<u32>>&>(edges),
            static_cast<u32>(k));
    }
};
