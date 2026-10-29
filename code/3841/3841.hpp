#include <algorithm>
#include <bit>
#include <charconv>
#include <string>
#include <string_view>
#include <vector>

#include "fenwick_tree/ft.hpp"
#include "fenwick_tree/ft_prefix.hpp"
#include "fenwick_tree/ft_xor.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"
#include "sync_stdio.hpp"

class Solution
{
public:
    inline static constexpr u32 kMaxN = 50'000;

    inline static u16 ancestors[std::bit_width(kMaxN)][kMaxN];

    inline static u32 masks[kMaxN];
    inline static u16 subtree_begin[kMaxN];
    inline static u16 subtree_end[kMaxN];
    inline static u32 fenwick_buffer[kMaxN];

    [[nodiscard,
      gnu::noinline,
      gnu::no_sanitize_address,
      gnu::target("popcnt,bmi,bmi2")]]
    std::vector<bool> palindromePath(
        const u32 n,
        const std::vector<std::vector<int>>& edges,
        std::string_view s,
        const std::vector<std::string>& queries) const noexcept
    {
        u16 query_begin = 0, query_end = static_cast<u16>(queries.size());
        while (query_end != 0 && queries.data()[query_end - 1].front() == 'u')
        {
            --query_end;
        }
        if (query_end == 0) return {};

        for (u32 i = 0; i != n; ++i)
        {
            masks[i] = u32{1} << (s.data()[i] - 'a');
        }

        while (queries.data()[query_begin].front() == 'u')
        {
            const auto& query = queries.data()[query_begin++];
            u16 vertex = 0;
            const auto parsed = std::from_chars(
                query.data() + 7,
                query.data() + query.size(),
                vertex);
            masks[vertex] = u32{1} << (parsed.ptr[1] - 'a');
        }

        const auto vertex_count = static_cast<u16>(n);
        auto& parents = ancestors[0];
        auto& queue = ancestors[1];
        auto& height = ancestors[2];
        auto& degree = subtree_begin;
        auto& subtree_size = subtree_end;
        for (u16 u = 0; u != vertex_count; ++u)
        {
            parents[u] = 0;
            degree[u] = 0;
            height[u] = 0;
            subtree_size[u] = 1;
        }
        degree[0] = 2;
        for (const auto& edge : edges)
        {
            const auto u = static_cast<u16>(edge.data()[0]);
            const auto v = static_cast<u16>(edge.data()[1]);
            parents[u] ^= v;
            parents[v] ^= u;
            ++degree[u];
            ++degree[v];
        }
        u16 queue_size = 0;
        for (u16 u = 0; u != vertex_count; ++u)
        {
            queue[queue_size] = u;
            queue_size += degree[u] == 1;
        }
        for (u16 i = 0; i != queue_size; ++i)
        {
            const u16 u = queue[i], v = parents[u];
            subtree_size[v] += subtree_size[u];
            height[v] = iif(height[v] > height[u], height[v], height[u] + 1);
            parents[v] ^= u;
            queue[queue_size] = v;
            queue_size += --degree[v] == 1;
        }
        const auto levels = std::bit_width(height[0]);
        auto& next_position = ancestors[2];
        subtree_begin[0] = 0;
        next_position[0] = 1;
        for (u16 i = queue_size; i != 0;)
        {
            const u16 u = queue[--i], v = parents[u];
            subtree_begin[u] = next_position[v];
            subtree_end[u] += subtree_begin[u];
            next_position[v] = subtree_end[u];
            next_position[u] = subtree_begin[u] + 1;
        }

        for (int level = 1; level < levels; ++level)
        {
            for (u32 i = 0; i != n; ++i)
            {
                ancestors[level][i] =
                    ancestors[level - 1][ancestors[level - 1][i]];
            }
        }
        const auto find_lca =
            [levels] [[gnu::always_inline, gnu::no_sanitize_address]] (
                u16 a,
                u16 b)
        {
            const auto contains =
                [] [[gnu::always_inline, gnu::no_sanitize_address]] (
                    u16 ancestor,
                    u16 vertex)
            {
                return (subtree_begin[ancestor] <= subtree_begin[vertex]) &
                       (subtree_begin[vertex] < subtree_end[ancestor]);
            };
            if (contains(a, b)) return a;
            if (contains(b, a)) return b;
            for (int level = levels; level != 0;)
            {
                --level;
                const u16 ancestor = ancestors[level][a];
                a = iif(contains(ancestor, b), a, ancestor);
            }
            return ancestors[0][a];
        };

        std::fill_n(fenwick_buffer, n, u32{0});
        for (u32 i = 0; i != n; ++i)
        {
            fenwick_buffer[subtree_begin[i]] ^= masks[i];
            if (subtree_end[i] != n) fenwick_buffer[subtree_end[i]] ^= masks[i];
        }
        for (u32 i = 0; i != n; ++i)
        {
            const u32 parent = i | (i + 1);
            if (parent < n) fenwick_buffer[parent] ^= fenwick_buffer[i];
        }
        const FenwickTree<u32, u32, FenwickTreeXORTraits> parity_tree{
            fenwick_buffer,
            n};
        std::vector<bool> result;
        result.reserve(u32{query_end} - query_begin);
        for (u16 qi = query_begin; qi != query_end; ++qi)
        {
            const auto& query = queries.data()[qi];
            const bool update = query.front() == 'u';
            const char* text_end = query.data() + query.size();
            u16 u = 0;
            const auto parsed =
                std::from_chars(query.data() + (update ? 7 : 6), text_end, u);
            if (update)
            {
                const u32 mask = u32{1} << (parsed.ptr[1] - 'a');
                const u32 delta = masks[u] ^ mask;
                const u32 begin = subtree_begin[u], end = subtree_end[u];
                if (delta == 0) continue;
                for (u32 i = begin; i < n; i |= i + 1)
                {
                    fenwick_buffer[i] ^= delta;
                }
                for (u32 i = end; i < n; i |= i + 1)
                {
                    fenwick_buffer[i] ^= delta;
                }
                masks[u] = mask;
            }
            else
            {
                u16 v = 0;
                std::from_chars(parsed.ptr + 1, text_end, v);
                const u16 ancestor = find_lca(u, v);
                const u32 parity =
                    ft_prefix(parity_tree, subtree_begin[u] + 1u) ^
                    ft_prefix(parity_tree, subtree_begin[v] + 1u) ^
                    masks[ancestor];
                result.push_back((parity & (parity - 1)) == 0);
            }
        }
        return result;
    }
};
