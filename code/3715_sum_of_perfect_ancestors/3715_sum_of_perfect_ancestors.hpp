#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <vector>

#include "force_inline.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"

template <u32 n>
class Factorizer
{
public:
    std::array<u32, n + 1> spf{};
    std::array<u32, 10'000> primes;
    u32 num_primes = 0;

    Factorizer() noexcept  // NOLINT
    {
        for (u32 x = 2u; x <= n; ++x)
        {
            if (spf[x] == 0u)
            {
                spf[x] = x;
                primes[num_primes++] = x;
            }

            for (u32 prime_index = 0; prime_index != num_primes; ++prime_index)
            {
                u32 prime = primes[prime_index];
                const u64 prod64 = u64{prime} * u64{x};
                if (prod64 > n) break;
                u32 prod = static_cast<u32>(prod64);
                spf[prod] = prime;
                if (prime == spf[x]) break;
            }
        }
    }

    template <typename Callback>
    FORCE_INLINE void factorize(u32 x, Callback callback) const noexcept
    {
        while (x > 1)
        {
            u32 prime = spf[x], power = 0u;
            while (!(x % prime))
            {
                x /= prime;
                ++power;
            }
            callback(prime, power);
        }
    }
};

struct Node  // NOLINT
{
    u32 num_edges = 0;
    u32 offset = 0;
};

class Solution
{
public:
    inline static Node nodes[100'001];
    inline static u32 edges[200'001];
    inline static u32 kernels_cnts[100'001];
    inline static u32 dirty_cnts = 0;

    u32 n = 0;
    u64 r = 0;
    std::span<const u32> nums;

    inline static constexpr u32 kInvalid = 0xFFFFFFFF;

    inline static auto kernels = []()  // NOLINT
    {
        Factorizer<100'001> factorizer{};
        std::array<u32, 100'001> result{};

        for (u32 x = 1; x != result.size(); ++x)
        {
            u32& kernel = result[x] = 1u;
            factorizer.factorize(
                x,
                [&](u32 prime, u32 power)
                {
                    // if power is odd multiply kernel by prime
                    kernel *= iif(power & 1, prime, 1u);
                });
        }

        return result;
    }();

    void dfs(u32 parent_id, u32 node_id) noexcept
    {
        const u32 kernel = kernels[nums[node_id]];
        dirty_cnts = std::max(kernel, dirty_cnts);
        r += kernels_cnts[kernel]++;

        const auto& node = nodes[node_id];
        for (u32 edge_idx = node.offset,
                 edge_idx_end = node.offset + node.num_edges;
             edge_idx != edge_idx_end;
             ++edge_idx)
        {
            if (u32 child_id = edges[edge_idx]; child_id != parent_id)
            {
                dfs(node_id, child_id);
            }
        }

        --kernels_cnts[kernel];
    }

    void build_tree(const std::vector<std::vector<u32>>& edges_) noexcept
    {
        std::fill_n(nodes, n, Node{});

        for (auto& edge : edges_)
        {
            u32 a = edge[0], b = edge[1];
            nodes[a].num_edges++;
            nodes[b].num_edges++;
        }

        for (u32 i = 0, sum = 0; i != n; ++i)
        {
            auto& node = nodes[i];
            node.offset = sum;
            sum += node.num_edges;
            node.num_edges = 0;
        }

        for (auto& edge : edges_)
        {
            u32 a = edge[0], b = edge[1];
            Node& na = nodes[a];
            Node& nb = nodes[b];
            edges[na.offset + na.num_edges++] = b;
            edges[nb.offset + nb.num_edges++] = a;
        }
    }

    u64 sumOfAncestors(
        int n_,
        std::vector<std::vector<int>>& edges_,
        std::vector<int>& nums_) noexcept
    {
        std::ranges::fill_n(
            kernels_cnts,
            std::exchange(dirty_cnts, 0u) + 1,
            0u);
        n = static_cast<u32>(n_), r = 0;
        nums = std::span{reinterpret_cast<std::vector<u32>&>(nums_)};
        build_tree(reinterpret_cast<std::vector<std::vector<u32>>&>(edges_));
        dfs(kInvalid, 0);
        return r;
    }
};

#include "sync_stdio.hpp"
