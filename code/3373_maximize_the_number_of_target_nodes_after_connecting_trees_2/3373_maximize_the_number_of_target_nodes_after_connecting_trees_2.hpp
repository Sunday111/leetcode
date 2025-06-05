#pragma once

#include <bitset>
#include <vector>

class Solution
{
private:
    static uint32_t& get_prev_n()
    {
        static uint32_t prev_n = 0;
        return prev_n;
    }

    template <typename T, size_t num>
    static T* get_tagged_memory()
    {
        static T data[num];  // NOLINT
        return data;
    }

public:
    struct QueueEntry
    {
        uint32_t node : 17;
        uint32_t parent : 17;
    };

    Solution()
        : adj(get_tagged_memory<std::vector<uint32_t>, 100'000>()),
          queue(get_tagged_memory<QueueEntry, 100'000>()),
          even(get_tagged_memory<std::bitset<100'000>, 1>())
    {
    }

    template <bool record_even_odd>
    uint32_t compute_even_odd(const std::vector<std::vector<int>>& edges)
    {
        auto& prev_n = get_prev_n();
        for (uint32_t i = 0; i != prev_n; ++i) adj[i].clear();
        n = static_cast<uint32_t>(edges.size() + 1);
        prev_n = n;

        for (const auto& edge : edges)
        {
            auto a = static_cast<uint32_t>(edge[0]);
            auto b = static_cast<uint32_t>(edge[1]);
            adj[a].emplace_back(b);
            adj[b].emplace_back(a);
        }

        constexpr uint32_t root = 0;
        uint8_t is_even = 1;
        uint32_t cnt = 0;
        queue[0].node = root;
        queue[0].parent = n;
        for (uint32_t front = 0, back = 1; front != back; is_even = !is_even)
        {
            if (is_even) cnt += back - front;
            for (uint32_t stop = back; front != stop; ++front)
            {
                auto [node, parent] = queue[front];
                if constexpr (record_even_odd) (*even)[node] = is_even;
                for (auto neighbor_id : adj[node])
                {
                    if (neighbor_id == parent) continue;
                    queue[back].node = neighbor_id;
                    queue[back].parent = node;
                    ++back;
                }
            }
        }

        return cnt;
    }

    uint32_t n = 0;
    std::vector<uint32_t>* adj;
    QueueEntry* queue;
    std::bitset<100'000>* even;

    [[nodiscard]] std::vector<int> maxTargetNodes(
        std::vector<std::vector<int>>& edges1,
        std::vector<std::vector<int>>& edges2)
    {
        const uint32_t max_even_in_tree_2 = compute_even_odd<false>(edges2);
        const uint32_t longest_in_tree_2 =
            std::max(max_even_in_tree_2, n - max_even_in_tree_2);
        const uint32_t max_even_in_tree_1 = compute_even_odd<true>(edges1);
        const uint32_t max_odd_in_tree_1 = n - max_even_in_tree_1;
        const std::array choices{
            static_cast<int>(max_odd_in_tree_1 + longest_in_tree_2),
            static_cast<int>(max_even_in_tree_1 + longest_in_tree_2)};

        std::vector<int> result;
        result.reserve(n);
        for (uint32_t i = 0; i != n; ++i)
        {
            result.push_back(choices[(*even)[i]]);
        }

        return result;
    }
};
