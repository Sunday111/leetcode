#include <algorithm>
#include <cstdint>
#include <functional>
#include <tuple>
#include <utility>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <typename T>
class UnionFind
{
public:
    struct Node
    {
        T size;
        T parent;
    };

    [[gnu::always_inline]] constexpr UnionFind(Node* buffer, T size) noexcept
        : nodes(buffer)
    {
        for (T x = 0; x != size; ++x) nodes[x] = {.size = 1, .parent = x};
    }

    [[nodiscard, gnu::always_inline]] constexpr T find(T x) noexcept
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
    [[gnu::always_inline]] constexpr bool merge(T x, T y) noexcept
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

class Solution
{
public:
    using UF = UnionFind<u32>;
    using UFNode = typename UF::Node;
    inline static UFNode nodes[1000];
    inline static std::pair<u16, u16> q[1'000'000 / 2];
    inline static std::pair<u32, u32> p[1'000];
    inline static u32 qs = 0;

    inline static constexpr auto dist =
        [] [[gnu::always_inline]] (u16 i, u16 j) noexcept -> u32
    {
        auto [xi, yi] = p[i];
        auto [xj, yj] = p[j];
        u32 dx = std::max(xi, xj) - std::min(xi, xj);
        u32 dy = std::max(yi, yj) - std::min(yi, yj);
        return dx + dy;
    };

    inline static constexpr auto proj =
        [] [[gnu::always_inline]] (auto ij) noexcept -> u32
    {
        return std::apply(dist, ij);
    };

    inline static constexpr auto cmp = std::greater{};

    inline static constexpr auto heap_op =
        [] [[gnu::always_inline]] (auto&& f) noexcept
    {
        f(q, q + qs, cmp, proj);
    };

    [[gnu::target("avx2,bmi2"), nodiscard]]
    u32 minCostConnectPoints(std::vector<std::vector<int>>& points) noexcept
    {
        const u32 n = static_cast<u32>(points.size());
        if (n < 2) return 0;

        qs = 0;
        for (u32 i = 0; i != n; ++i)
        {
            for (u32 j = i + 1; j != n; ++j)
            {
                q[qs++] = {i, j};
            }

            auto& pt = points[i];
            p[i] = {pt[0] + 1'000'000, pt[1] + 1'000'000};
        }

        heap_op(std::ranges::make_heap);

        u32 cost = 0;
        UF uf(nodes, n);

        while (nodes[uf.find(0)].size != n)
        {
            auto [i, j] = q[0];
            cost += dist(i, j) & -u32{uf.merge(i, j)};
            heap_op(std::ranges::pop_heap);
            --qs;
        }

        return cost;
    }
};
#include <algorithm>
#include <cstdint>
#include <functional>
#include <tuple>
#include <utility>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <typename T>
class UnionFind
{
public:
    struct Node
    {
        T size;
        T parent;
    };

    [[gnu::always_inline]] constexpr UnionFind(Node* buffer, T size) noexcept
        : nodes(buffer)
    {
        for (T x = 0; x != size; ++x) nodes[x] = {.size = 1, .parent = x};
    }

    [[nodiscard, gnu::always_inline]] constexpr T find(T x) noexcept
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
    [[gnu::always_inline]] constexpr bool merge(T x, T y) noexcept
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

class Solution
{
public:
    using UF = UnionFind<u32>;
    using UFNode = typename UF::Node;
    inline static UFNode nodes[1000];
    inline static std::pair<u16, u16> q[1'000'000 / 2];
    inline static std::pair<u32, u32> p[1'000];
    inline static constexpr auto dist =
        [] [[gnu::always_inline]] (u16 i, u16 j) noexcept -> u32
    {
        auto [xi, yi] = p[i];
        auto [xj, yj] = p[j];
        u32 dx = std::max(xi, xj) - std::min(xi, xj);
        u32 dy = std::max(yi, yj) - std::min(yi, yj);
        return dx + dy;
    };
    inline static constexpr auto proj =
        [] [[gnu::always_inline]] (auto ij) noexcept -> u32
    {
        return std::apply(dist, ij);
    };
    inline static constexpr auto cmp = std::greater{};

    [[gnu::target("avx2,bmi2"), nodiscard]]
    u32 minCostConnectPoints(std::vector<std::vector<int>>& points) noexcept
    {
        const u32 n = static_cast<u32>(points.size());
        if (n < 2) return 0;

        auto qe = q;
        for (u32 i = 0; i != n; ++i)
        {
            for (u32 j = i + 1; j != n; ++j)
            {
                *qe++ = {i, j};
            }

            auto& pt = points[i];
            p[i] = {pt[0] + 1'000'000, pt[1] + 1'000'000};
        }

        std::ranges::make_heap(q, qe, cmp, proj);

        u32 cost = 0;
        UF uf(nodes, n);

        while (nodes[uf.find(0)].size != n)
        {
            auto [i, j] = q[0];
            cost += dist(i, j) & -u32{uf.merge(i, j)};
            std::ranges::pop_heap(q, qe--, cmp, proj);
        }

        return cost;
    }
};
