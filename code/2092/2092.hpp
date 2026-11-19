#include <algorithm>
#include <vector>

using u32 = uint32_t;

class Solution
{
public:
    struct Node
    {
        u32 degree{};
        u32 offset{};
    };

    [[nodiscard]] static std::vector<int> findAllPeople(
        u32 n,
        std::vector<std::vector<int>>& meetings_,
        u32 firstPerson)
    {
        auto& meetings =
            reinterpret_cast<std::vector<std::vector<u32>>&>(meetings_);

        static Node g[100'000];
        std::fill_n(g, n, Node{});

        constexpr u32 kNotVisited = 200'000;
        static u32 visit_time[100'000];
        std::fill_n(visit_time, n, kNotVisited);

        static std::pair<u32, u32> links[200'000];

        for (auto& meeting : meetings)
        {
            u32 p1 = static_cast<u32>(meeting[0]);
            u32 p2 = static_cast<u32>(meeting[1]);
            g[p1].degree += 1;
            g[p2].degree += 1;
        }

        u32 offset = 0;
        for (u32 i = 0; i != n; ++i)
        {
            auto& node = g[i];
            node.offset = offset;
            offset += node.degree;
            node.degree = 0;
        }

        for (auto& meeting : meetings)
        {
            u32 p1 = meeting[0], p2 = meeting[1], t = meeting[2];
            auto &n1 = g[p1], &n2 = g[p2];
            links[n1.offset + n1.degree++] = {t, p2};
            links[n2.offset + n2.degree++] = {t, p1};
        }

        static std::pair<u32, u32> q[200'000];
        u32 qs = 0;

        q[qs++] = {0, 0};
        q[qs++] = {0, firstPerson};
        std::make_heap(q, q + qs, std::greater{});

        std::vector<int> result;
        result.reserve(n);

        while (qs && result.size() != n)
        {
            std::ranges::pop_heap(q, q + qs, std::greater{});
            auto [time, node_id] = q[--qs];
            if (visit_time[node_id] == kNotVisited)
            {
                result.push_back(static_cast<int>(node_id));
            }

            // Already propagated secret from here
            if (time >= visit_time[node_id])
            {
                continue;
            }

            visit_time[node_id] = time;

            auto& node = g[node_id];
            for (u32 link_index = node.offset, end = link_index + node.degree;
                 link_index != end;
                 ++link_index)
            {
                auto& [link_time, link_target] = links[link_index];
                if (time <= link_time && link_time <= visit_time[link_target])
                {
                    q[qs++] = links[link_index];
                    std::push_heap(q, q + qs, std::greater{});
                }
            }
        }

        return result;
    }
};
