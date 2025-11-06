#include <algorithm>
#include <vector>

using u32 = uint32_t;
using u8 = uint32_t;

struct GroupInfo
{
    u32 begin = 0;
    u32 end = 0;
};

struct Node
{
    u32 offset = 0;
    u32 num_links = 0;
};

class Solution
{
public:
    void processQueries(
        u32 c,
        std::vector<std::vector<u32>>& connections,
        std::vector<std::vector<u32>>& queries,
        std::vector<u32>& result)
    {
        Node nodes[100'002];
        u32 child_array[200'004];
        std::fill_n(nodes, c + 1, Node{});

        for (auto& connection : connections)
        {
            u32 a = connection[0], b = connection[1];
            nodes[a].num_links++;
            nodes[b].num_links++;
        }

        for (u32 offset = 0, node_id = 1; node_id <= c; ++node_id)
        {
            auto& node = nodes[node_id];
            node.offset = offset;
            offset += std::exchange(node.num_links, 0);
        }

        for (auto& connection : connections)
        {
            u32 aid = connection[0], bid = connection[1];
            auto &a = nodes[aid], &b = nodes[bid];
            child_array[a.offset + a.num_links++] = bid;
            child_array[b.offset + b.num_links++] = aid;
        }

        static u32 nodes_groups[100'002];
        std::fill_n(nodes_groups, c + 1, 0u);

        static u32 groups_nodes_arr[100'002];
        u32 groups_nodes_arr_offset = 0;

        GroupInfo groups[100'002];
        u32 gs = 1;

        static u32 q[100'002];
        u32 qs = 0;

        u32 next_group = 1;

        for (u32 i = 1; i <= c; ++i)
        {
            if (nodes_groups[i]) continue;
            u32 group_id = next_group++;
            auto& group = groups[gs++] = {
                .begin = groups_nodes_arr_offset,
                .end = groups_nodes_arr_offset,
            };

            q[qs++] = i;

            while (qs)
            {
                auto node_id = q[--qs];
                if (nodes_groups[node_id]) continue;
                nodes_groups[node_id] = group_id;
                groups_nodes_arr[group.end++] = node_id;

                auto& node = nodes[node_id];
                u32 child_idx = node.offset;
                u32 end = child_idx + node.num_links;
                while (child_idx != end) q[qs++] = child_array[child_idx++];
            }

            groups_nodes_arr_offset = group.end;
        }

        for (u32 i = 0; i != gs; ++i)
        {
            auto& group = groups[i];
            std::sort(
                groups_nodes_arr + group.begin,
                groups_nodes_arr + group.end);
        }

        result.reserve(queries.size());

        static u8 status[100'001];
        std::fill_n(status, c + 1, 1);

        for (auto& query : queries)
        {
            u32 station = query[1];
            u32 group_id = nodes_groups[station];
            auto& group = groups[group_id];
            if (query[0] == 1)
            {
                u32& ans = result.emplace_back(0xFFFFFFFF);
                if (status[station])
                {
                    ans = station;
                    continue;
                }

                while (group.begin != group.end &&
                       !status[groups_nodes_arr[group.begin]])
                {
                    ++group.begin;
                }

                if (group.begin != group.end)
                {
                    ans = groups_nodes_arr[group.begin];
                }
            }
            else
            {
                status[station] = false;
            }
        }
    }

    std::vector<int> processQueries(
        u32 c,
        std::vector<std::vector<int>>& connections,
        std::vector<std::vector<int>>& queries)
    {
        std::vector<int> result;
        processQueries(
            c,
            reinterpret_cast<std::vector<std::vector<u32>>&>(connections),
            reinterpret_cast<std::vector<std::vector<u32>>&>(queries),
            reinterpret_cast<std::vector<u32>&>(result));
        return result;
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
