#include <bit>
#include <concepts>
#include <cstdint>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>



using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};


struct Node
{
    u32 degree;
    u32 offset;
    u32 depth_idx;
};

inline static constexpr u32 kMaxN = 100'000;
inline static constexpr u32 kMOD = 1000000007;
inline static u32 st_data[(std::bit_width(kMaxN)+1) * 2 * kMaxN];       // NOLINT
inline static u32 kAns[kMaxN];               // NOLINT
inline static Node nodes[kMaxN];             // NOLINT
inline static u32 links[2*kMaxN];              // NOLINT
inline static u32 depths[2*kMaxN];             // NOLINT
inline static std::pair<u32, u32> q[kMaxN];  // NOLINT

class SparseTable
{
    u32 n;

public:
    [[gnu::always_inline]]
    SparseTable(const u32* data, u32 sz) noexcept
    {
        n = sz;

        u32 max_k = (31 - std::countl_zero(n) + 1) & 63;
        std::copy_n(data, n, st_data);

        for (u32 k = 1; k != max_k; k++)
        {
            for (u32 i = 0; i + (1 << k) <= n; i++)
            {
                u32 t1 = (k - 1) * n + i, t2 = t1 + (1u << (k - 1));
                st_data[k * n + i] = std::min(st_data[t1], st_data[t2]);
            }
        }
    }

    [[nodiscard, gnu::always_inline]]
    u32 queryMin(u32 l, u32 r) const noexcept
    {
        u32 k = (31 - std::countl_zero(r - l + 1u)) & 63, t = r - (1u << k) + 1;
        return std::min(st_data[k * n + l], st_data[k * n + t]);
    }
};

inline static const auto kAnsInit = []
{
    kAns[0] = 0;
    kAns[1] = 1;
    for (u32 n = 2; n != kMaxN; ++n)
    {
        kAns[n] = (u64{kAns[n - 1]} * 2) % kMOD;
    }

    return 0;
}();

class Solution
{
public:
    static std::vector<u32> impl(
        const std::vector<std::vector<u32>>& edges,
        const std::vector<std::vector<u32>>& queries) noexcept
    {
        const u32 n = static_cast<u32>(edges.size() + 1);

        std::fill_n(nodes, n, Node{0, 0, 0});

        for (auto& e : edges)
        {
            u32 i = e[0] - 1, j = e[1] - 1;
            nodes[i].degree++;
            nodes[j].degree++;
        }

        for (u32 o = 0, i = 0; i != n; ++i)
        {
            auto& node = nodes[i];
            node.offset = o;
            o += std::exchange(node.degree, 0);
        }

        for (auto& edge : edges)
        {
            u32 i = edge[0] - 1, j = edge[1] - 1;
            auto &ni = nodes[i], &nj = nodes[j];
            links[ni.offset + ni.degree++] = j;
            links[nj.offset + nj.degree++] = i;
        }

        // queue q element is {tree node id, link index}
        q[1] = {0, 0};

        // euler tour technique (kind of)
        for (u32 qe = 2, ndi = 1; qe != 1; )
        {
            auto& [i, link_index] = q[qe - 1];
            auto& ni = nodes[i];
            bool pop = link_index == ni.degree;
            u32 j = links[ni.offset + link_index];
            q[qe] = {j, 0};
            auto& nj = nodes[j];
            u32 i_parent = q[qe - 2].first;
            bool j_valid = !(pop | (j == i_parent));
            qe += j_valid - pop;
            depths[ndi] = qe - 2;
            nj.depth_idx = iif(j_valid, ndi, nj.depth_idx);
            link_index += !pop;
            ndi += pop | j_valid;
        }

        SparseTable st(depths, 2 * (n - 1));
        return std::ranges::to<std::vector>(
            queries |
            std::views::transform(
                [&](auto& query)
                {
                    u32 i = query[0] - 1, j = query[1] - 1;
                    u32 a = nodes[i].depth_idx, b = nodes[j].depth_idx;
                    auto min_depth =
                        st.queryMin(std::min(a, b), std::max(a, b));
                    return kAns[depths[a] + depths[b] - 2 * min_depth];
                }));
    }

    std::vector<int> assignEdgeWeights(
        const std::vector<std::vector<int>>& edges,
        const std::vector<std::vector<int>>& queries) noexcept
    {
        std::vector<int> r;
        reinterpret_cast<std::vector<u32>&>(r) = impl(
            reinterpret_cast<const std::vector<std::vector<u32>>&>(edges),
            reinterpret_cast<const std::vector<std::vector<u32>>&>(queries));
        return r;
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
