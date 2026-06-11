#include <cstdint>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

inline constexpr u32 kMOD = 1'000'000'007;
inline static constexpr u32 kMaxN = 100'000;
inline static u32 kAns[kMaxN];  // NOLINT

inline static const auto kAnsInit = []
{
    kAns[0] = 1;
    for (u32 n = 1; n != kMaxN; ++n)
    {
        kAns[n] = (u64{kAns[n - 1]} * 2) % kMOD;
    }

    return 0;
}();

u32 tree_height(const std::vector<std::vector<u32>>& edges)
{
    static u32 degree[kMaxN];
    static u32 offset[kMaxN];
    static u32 links[kMaxN * 2];
    static std::pair<u32, u32> q[kMaxN + 1];

    const u32 n = static_cast<u32>(edges.size() + 1);

    std::fill_n(degree, n, 0);

    for (auto& e : edges)
    {
        u32 i = e[0] - 1, j = e[1] - 1;
        degree[i]++;
        degree[j]++;
    }

    for (u32 o = 0, i = 0; i != n; ++i)
    {
        offset[i] = o;
        o += degree[i];
        degree[i] = 0;
    }

    for (auto& edge : edges)
    {
        u32 i = edge[0] - 1, j = edge[1] - 1;
        links[offset[i] + degree[i]++] = j;
        links[offset[j] + degree[j]++] = i;
    }

    u32 qb = 0, qe = 0, r = 0;
    q[qe++] = {0, 0};

    while (qb != qe)
    {
        for (u32 stop = qe; qb != stop; ++qb)
        {
            auto [parent, id] = q[qb];
            for (u32 link_index = offset[id],
                     link_end = link_index + degree[id];
                 link_index != link_end;
                 ++link_index)
            {
                u32 dst = links[link_index];
                q[qe] = {id, dst};
                qe += dst != parent;
            }
        }

        ++r;
    }

    return r;
}

class Solution
{
public:
    u32 assignEdgeWeights(std::vector<std::vector<int>>& edges) noexcept
    {
        return kAns
            [tree_height(
                 reinterpret_cast<std::vector<std::vector<u32>>&>(edges)) -
             2];
    }
};
