#include <algorithm>
#include <vector>

using u32 = uint32_t;
using i64 = int64_t;

class Solution
{
public:
    struct Node
    {
        i64 v = 0;
        u32 prev = 0;
        u32 next : 31 = 0;
        u32 removed : 1 = 0;
    };

    u32 minimumPairRemoval(std::vector<int>& nums) noexcept
    {
        u32 r = 0, n = static_cast<u32>(nums.size());
        static Node nodes[100'001];
        for (u32 i = 0; i != n; ++i)
        {
            nodes[i] = {
                .v = nums[i],
                .prev = i - 1,
                .next = i + 1,
                .removed = false,
            };
        }

        nodes[0].prev = 0;
        nodes[n].v = 0;
        nodes[n].next = n;
        nodes[n].removed = true;

        static std::pair<i64, u32> heap[300'000];
        u32 hs = n - 1;
        for (u32 i = 0, j = 1; j != n; ++i, ++j)
        {
            heap[i] = {nodes[i].v + nodes[j].v, i};
        }

        constexpr auto heap_cmp = std::greater{};

        std::ranges::make_heap(heap, heap + hs, heap_cmp);

        auto merge = [&]() -> std::pair<u32, u32>
        {
            ++r;
            while (true)
            {
                std::ranges::pop_heap(heap, heap + hs, heap_cmp);
                auto [ps, i] = heap[hs - 1];
                auto& node = nodes[i];
                i64 s = node.v + nodes[node.next].v;

                if (node.removed || node.next == n)
                {
                    --hs;
                }
                else if (s != ps)
                {
                    heap[hs - 1] = {s, i};
                    std::ranges::push_heap(heap, heap_cmp);
                }
                else
                {
                    node.v = s;

                    u32 removed = node.next;
                    node.next = nodes[node.next].next;

                    nodes[node.next].prev = i;
                    nodes[removed].removed = true;

                    if (node.next != n)
                    {
                        heap[hs - 1] = {node.v + nodes[node.next].v, i};
                        std::ranges::push_heap(heap, heap + hs, heap_cmp);
                    }
                    else
                    {
                        --hs;
                    }

                    if (node.prev != n)
                    {
                        heap[hs++] = {node.v + nodes[node.prev].v, node.prev};
                        std::ranges::push_heap(heap, heap + hs, heap_cmp);
                    }

                    return {i, removed};
                }
            }

            std::unreachable();
        };

        for (u32 i = 0; nodes[i].next != n;)
        {
            auto &curr = nodes[i], &next = nodes[curr.next];

            if (curr.v <= next.v)
            {
                i = curr.next;
                continue;
            }

            if (auto [updated, removed] = merge(); updated <= i)
            {
                auto& updated_node = nodes[updated];
                if (nodes[updated_node.prev].v > updated_node.v)
                {
                    i = updated_node.prev;
                }

                if (removed == i ||
                    (updated_node.next != n &&
                     updated_node.v > nodes[updated_node.next].v))
                {
                    i = updated;
                }
            }
        }

        return r;
    }
};
