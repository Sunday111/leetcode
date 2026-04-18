#include <unordered_map>
#include <vector>

#include "bump_allocator.hpp"
#include "bump_hash_map.hpp"
#include "bump_vector.hpp"
#include "cast.hpp"
#include "integral_aliases.hpp"
#include "namespaces.hpp"
#include "swap_if.hpp"

struct UFNode
{
    u32 parent;
    u32 size;
};

class Solution
{
public:
    static u32 impl(
        const std::vector<u32>& s,
        const std::vector<u32>& t,
        const std::vector<std::vector<u32>>& swaps) noexcept
    {
        static UFNode nodes[100'000];

        const u32 n = cast<u32>(s.size());

        for (u32 i = 0; i != n; ++i)
        {
            nodes[i].parent = i;
            nodes[i].size = 1;
        }

        auto find = [&] [[gnu::always_inline]] (u32 i) -> u32
        {
            u32 root = i;
            while (nodes[root].parent != root)
            {
                root = nodes[root].parent;
            }
            while (i != root)
            {
                u32 next = nodes[i].parent;
                nodes[i].parent = root;
                i = next;
            }
            return root;
        };

        for (auto& swp : swaps)
        {
            u32 ra = find(swp[0]), rb = find(swp[1]);
            swap_if(nodes[rb].size < nodes[ra].size, ra, rb);
            auto &a = nodes[ra], &b = nodes[rb];
            a.parent = rb;
            b.size += a.size & -u32{ra != rb};
        }

        using Storage = GlobalBufferStorage<1 << 23>;
        auto _ = Storage::Instance().StartArena();
        BumpVector<ObjectWithoutDtor<BumpHashMap<u32, int, Storage>>, Storage>
            groups;
        groups.reserve(n);

        static u32 node_to_group[100001];
        std::fill_n(node_to_group, n, ~u32{});
        for (u32 i = 0; i != n; ++i)
        {
            u32 root = find(i);
            auto& gi = node_to_group[root];
            if (gi == ~u32())
            {
                gi = cast<u32>(groups.size());
                groups.emplace_back();
                groups.back().get().reserve(nodes[root].size);
            }

            if (u32 sv = s[i], tv = t[i]; sv != tv)
            {
                auto& g = groups[gi];
                ++g.get()[sv];
                --g.get()[tv];
            }
        }

        u32 dist = 0;
        for (auto& g : groups)
        {
            for (auto& v : g.get() | stdv::values)
            {
                dist += cast<u32>(std::abs(v));
            }
        }

        return dist / 2;
    }

    u32 minimumHammingDistance(
        const std::vector<int>& source,
        const std::vector<int>& target,
        const std::vector<std::vector<int>>& allowedSwaps) const noexcept
    {
        return impl(
            reinterpret_cast<const std::vector<u32>&>(source),
            reinterpret_cast<const std::vector<u32>&>(target),
            reinterpret_cast<const std::vector<std::vector<u32>>&>(
                allowedSwaps));
    }
};
