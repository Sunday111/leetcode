#include <vector>

#include "integral_aliases.hpp"
#include "to.hpp"

class Solution
{
public:
    inline static constexpr u16 max_nodes = 30000;
    inline static u16 link[max_nodes * 2];
    inline static u16 degree[max_nodes];
    inline static u16 offset[max_nodes];
    const u32* value{};

    u32 r = 0, k = 0;

    u32 dfs(u32 parent = 0xFFFF, u32 node = 0)
    {
        u32 s = value[node];
        while (degree[node])
        {
            auto l = link[offset[node] + --degree[node]];
            if (l != parent)
            {
                s += dfs(node, l);
            }
        }
        s %= k;
        r += !s;
        return s;
    }

    u32 maxKDivisibleComponents(
        u32 n,
        std::vector<std::vector<int>>& edges,
        const std::vector<int>& values,
        u32 k_)
    {
        k = k_;
        value = reinterpret_cast<const u32*>(values.data());
        std::fill_n(link, n * 2, 0);
        std::fill_n(degree, n, 0);

        for (auto& edge : edges)
        {
            u16 a = cast<u16>(edge[0]), b = cast<u16>(edge[1]);
            degree[a]++;
            degree[b]++;
        }

        for (u16 i = 0, o = 0; i != n; ++i)
        {
            offset[i] = o;
            o += degree[i];
            degree[i] = 0;
        }

        for (auto& edge : edges)
        {
            u16 a = cast<u16>(edge[0]), b = cast<u16>(edge[1]);
            link[offset[a] + degree[a]++] = b;
            link[offset[b] + degree[b]++] = a;
        }

        dfs();
        return r;
    }
};
