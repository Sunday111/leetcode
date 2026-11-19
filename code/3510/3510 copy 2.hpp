#include <algorithm>
#include <print>
#include <ranges>
#include <span>
#include <unordered_set>
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
        u32 r = 0, n = static_cast<u32>(nums.size()), left_bound = 0,
            right_bound = n + 1;
        static Node nodes[100'002];

        nodes[left_bound] = {
            .v = std::numeric_limits<i64>::lowest(),
            .prev = 0,
            .next = 1,
            .removed = 1,
        };

        for (u32 i = 1; int v : nums)
        {
            nodes[i++] = {
                .v = v,
                .prev = i - 1,
                .next = i + 1,
                .removed = false,
            };
        }

        nodes[right_bound] = {
            .v = std::numeric_limits<i64>::max(),
            .prev = n,
            .next = right_bound,
            .removed = 1,
        };

        static std::pair<i64, u32> heap[300'000];
        u32 hs = 0;
        for (u32 i = 1; i != n; ++i)
        {
            heap[hs++] = {nodes[i].v + nodes[i + 1].v, i};
        }

        // [[maybe_unused]] auto print_state = [&]()
        // {
        //     std::println("-------------------------------");
        //     std::println("hs: {}", hs);
        //     for (u32 i = nodes[left_bound].next; i != right_bound;)
        //     {
        //         auto& node = nodes[i];
        //         std::println("    {:>10}: {}", "v", node.v);
        //         std::println("    {:>10}: {}", "prev", node.prev);
        //         std::println("    {:>10}: {}", "next", u32{node.next});
        //         std::println("    {:>10}: {}", "removed",
        //         bool{node.removed}); std::println("
        //         -------------------------------"); i = node.next;
        //     }
        // };

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

                if (node.removed || node.next == right_bound)
                {
                    --hs;
                    continue;
                }

                i64 s = node.v + nodes[node.next].v;
                if (s != ps)
                {
                    heap[hs - 1] = {s, i};
                    std::ranges::push_heap(heap, heap + hs, heap_cmp);
                }
                else
                {
                    node.v = s;

                    u32 removed = node.next;
                    node.next = nodes[node.next].next;

                    nodes[node.next].prev = i;
                    nodes[removed].removed = true;

                    if (node.next != right_bound)
                    {
                        heap[hs - 1] = {node.v + nodes[node.next].v, i};
                        std::ranges::push_heap(heap, heap + hs, heap_cmp);
                    }
                    else
                    {
                        --hs;
                    }

                    if (node.prev != left_bound)
                    {
                        heap[hs++] = {node.v + nodes[node.prev].v, node.prev};
                        std::ranges::push_heap(heap, heap + hs, heap_cmp);
                    }

                    return {i, removed};
                }
            }

            std::unreachable();
        };

        // std::unordered_set<u32> bad;
        // print_state();

        for (u32 i = 1; nodes[i].next != right_bound;)
        {
            // print_state();
            auto &curr = nodes[i], &next = nodes[curr.next];

            if (curr.v <= next.v)
            {
                i = curr.next;
                continue;
            }

            auto [updated, removed] = merge();
            if (updated <= i)
            {
                auto& updated_node = nodes[updated];
                if (nodes[updated_node.prev].v > updated_node.v)
                {
                    i = updated_node.prev;
                }

                if (removed == i || updated_node.v > nodes[updated_node.next].v)
                {
                    i = updated;
                }
            }
        }

        return r;
    }
};
