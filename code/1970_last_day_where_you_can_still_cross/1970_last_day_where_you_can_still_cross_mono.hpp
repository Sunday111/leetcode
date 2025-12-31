#include <cstdint>
#include <utility>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

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

    FORCE_INLINE constexpr void merge(T x, T y) noexcept
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
    }

    Node* nodes;
};

class Solution
{
public:
    [[nodiscard]] FORCE_INLINE bool bitset_contains(
        const u64* bitset,
        u16 i) noexcept
    {
        return bitset[i >> 6] & (1ul << (i & 63));
    }

    FORCE_INLINE void bitset_add(u64* bitset, u16 i) noexcept
    {
        bitset[i >> 6] |= (1ul << (i & 63));
    }

    size_t
    latestDayToCross(u16 row, u16 col, std::vector<std::vector<int>>& cells)
    {
        if (row == 1) return cells.size();
        if (col == 1) return 0;

        using UF = UnionFind<u16>;
        using Node = UF::Node;

        constexpr u32 K = (10000 + 2) * (2 + 2);
        constexpr u32 max_words = (K / 64) + 1;

        static Node nodes[K];

        const u16 h = row + 2, w = col + 2;
        UF uf(nodes, w * h);

        static u64 water[max_words];
        u16 num_words = ((w * h) / 64) + 1;
        std::fill_n(water, num_words, 0);

        // Flood left and right columns
        {
            u16 l = 0, r = w - 1;
            bitset_add(water, l), bitset_add(water, r);
            for (u16 y = 1; y != h; ++y)
            {
                u16 nl = l + w, nr = r + w;
                uf.merge(l, nl), uf.merge(r, nr);
                l = nl, r = nr;
                bitset_add(water, l), bitset_add(water, r);
            }
        }

        const int offsets[8]{-w - 1, -w, -w + 1, -1, 1, w - 1, w, w + 1};
        u16 left = 0, right = w - 1, day = 0;

        for (auto& cell : cells)
        {
            u16 i = (cell[1] + w * cell[0]) & 0xFFFF;
            bitset_add(water, i);

            // merge with flooded neighbors
            for (int offset : offsets)
            {
                u16 j = (i + offset) & 0xFFFF;
                if (bitset_contains(water, j)) uf.merge(i, j);
            }

            if (uf.find(left) == uf.find(right)) return day;

            ++day;
        }

        return cells.size();
    }
};
