#include <algorithm>
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
    using UF = UnionFind<u32>;
    using Node = UF::Node;

    [[nodiscard]] static constexpr u32 largestIsland(
        const std::vector<std::vector<int>>& grid) noexcept
    {
        u16 h = grid.size() & 0xFFFF, w = grid[0].size() & 0xFFFF;

        static Node nodes[500 * 500];
        UF uf(nodes, u32{w} * u32{h});

        constexpr u16 dx[4]{0xFFFF, 1, 0, 0};
        constexpr u16 dy[4]{0, 0, 0xFFFF, 1};

        auto to_idx = [&](u16 x, u16 y) INLINE_LAMBDA noexcept
        {
            return u32{y} * u32{w} + u32{x};
        };

        for (u16 y = 0; y != h; ++y)
        {
            for (u16 x = 0; x != w; ++x)
            {
                u32 i = to_idx(x, y);
                if (!grid[y][x]) continue;

                for (u8 p = 0; p != 4; ++p)
                {
                    u16 nx = x + dx[p], ny = y + dy[p];
                    u32 j = to_idx(nx, ny);

                    if (nx < w && ny < h && grid[ny][nx])
                    {
                        uf.merge(i, j);
                    }
                }
            }
        }

        u32 ans = 0;
        for (u16 y = 0; y != h; ++y)
        {
            for (u16 x = 0; x != w; ++x)
            {
                if (grid[y][x])
                {
                    ans = std::max(ans, nodes[to_idx(x, y)].size);
                    continue;
                }

                u32 near[4], num_near = 0;

                for (u8 p = 0; p != 4; ++p)
                {
                    u16 nx = x + dx[p], ny = y + dy[p];
                    u32 j = to_idx(nx, ny);

                    if (nx < w && ny < h && grid[ny][nx])
                    {
                        near[num_near] = uf.find(j);
                        num_near++;
                    }
                }

                std::ranges::sort(near, near + num_near);
                u32* end = std::ranges::unique(near, near + num_near).begin();
                u32 merged_size = 1;
                for (u32* it = near; it != end; ++it)
                {
                    merged_size += nodes[*it].size;
                }

                ans = std::max(ans, merged_size);
            }
        }

        return ans;
    }
};
