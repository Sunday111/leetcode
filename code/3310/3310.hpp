#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

#include "integral_aliases.hpp"
#include "namespaces.hpp"
#include "sync_stdio.hpp"

class Solution
{
public:
    struct Node
    {
        u32 degree;
        u32 offset;
    };

    inline static Node nodes[100'000];
    inline static u32 links[200'000];
    inline static u32 q[100'001];
    inline static u64 queued[100'001 / 64 + 1];

    [[gnu::always_inline]] static bool get_bit(const u64* p, u32 i) noexcept
    {
        return p[i >> 6] & (u64{1} << (i & 63));
    }

    [[gnu::always_inline]] static bool add_bit(u64* p, u32 i) noexcept
    {
        auto& w = p[i >> 6];
        auto prev = w;
        w |= (u64{1} << (i & 63));
        return prev != w;
    }

    [[nodiscard, gnu::always_inline]] static std::span<const u32> get_links(
        const Node& x) noexcept
    {
        return std::span{links + x.offset, x.degree};
    };

    [[nodiscard]] static std::vector<u32> impl(
        u32 n,
        const u32 k,
        const std::vector<std::vector<u32>>& edges) noexcept
    {
        const auto indices = stdv::iota(u32{}, n);
        std::fill_n(nodes, n, Node{0, 0});

        for (auto& e : edges)
        {
            u32 i = e[0];
            nodes[i].degree++;
        }

        for (u32 o = 0; auto& x : nodes | stdv::take(n))
        {
            x.offset = o;
            o += std::exchange(x.degree, 0);
        }

        for (auto& edge : edges)
        {
            auto& x = nodes[edge[0]];
            links[x.offset + x.degree++] = edge[1];
        }

        constexpr auto is_queued =
            std::bind(get_bit, queued, std::placeholders::_1);
        constexpr auto not_queued = std::not_fn(is_queued);

        {
            u32 qs = 0;
            std::fill_n(queued, (n / 64) + 1, u64{});

            auto enqueue = [&] [[gnu::always_inline]] (u32 i) noexcept
            {
                q[qs] = i;
                qs += add_bit(queued, i);
            };

            enqueue(k);

            while (qs)
            {
                stdr::for_each(get_links(nodes[q[--qs]]), enqueue);
            }
        }

        const bool make_full = stdr::any_of(
            indices | stdv::filter(not_queued),
            [&] [[gnu::always_inline]] (u32 i)
            { return stdr::any_of(get_links(nodes[i]), is_queued); });

        std::vector<u32> r;
        r.reserve(n);
        const auto append =
            std::bind(stdr::copy, std::placeholders::_1, std::back_inserter(r));
        if (make_full)
        {
            append(indices);
        }
        else
        {
            append(indices | stdv::filter(not_queued));
        }
        return r;
    }

    std::vector<int> remainingMethods(
        u32 n,
        u32 k,
        const std::vector<std::vector<int>>& invocations)
    {
        std::vector<int> r;
        reinterpret_cast<std::vector<u32>&>(r) = impl(
            n,
            k,
            reinterpret_cast<const std::vector<std::vector<u32>>&>(
                invocations));
        return r;
    }
};
