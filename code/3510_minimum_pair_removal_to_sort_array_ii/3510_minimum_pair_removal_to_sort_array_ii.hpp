#include <bitset>
#include <set>
#include <vector>

#include "bump_set.hpp"

using u32 = uint32_t;
using i64 = int64_t;

using SolutionStorage = GlobalBufferStorage<1u << 25>;

class Solution
{
public:
    struct Node
    {
        i64 v = 0;
        u32 prev = 0;
        u32 next = 0;
    };

    u32 minimumPairRemoval(std::vector<int>& nums) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();

        u32 r = 0, n = static_cast<u32>(nums.size()), left_bound = 0,
            right_bound = n + 1;
        Node* nodes = BumpAllocator<Node, SolutionStorage>{}.allocate(n + 2);

        std::bitset<1 << 17> removed;
        ObjectWithoutDtor<BumpSet<std::pair<i64, u32>, SolutionStorage>> set;

        removed[left_bound] = 1;
        nodes[left_bound] = {
            .v = std::numeric_limits<i64>::lowest(),
            .prev = 0,
            .next = 1,
        };

        u32 num_bad = 0;
        for (u32 i = 1; i != right_bound; ++i)
        {
            i64 v = nums[i - 1];

            nodes[i] = {
                .v = v,
                .prev = i - 1,
                .next = i + 1,
            };

            if (i != n)
            {
                i64 vi = v;
                i64 vj = nums[i];
                num_bad += (vi > vj);
                set->emplace(vi + vj, i);
            }
        }

        removed[right_bound] = 1;
        nodes[right_bound] = {
            .v = std::numeric_limits<i64>::max(),
            .prev = n,
            .next = right_bound,
        };

        while (num_bad)
        {
            auto pop_node = set->extract(*set->begin());
            const auto [next_sum, i] = pop_node.value();
            auto& node = nodes[i];
            auto& prev = nodes[node.prev];
            auto& next = nodes[node.next];
            auto& next_next = nodes[next.next];

            if (removed[i] || node.next == right_bound) continue;

            i64 new_value = node.v + nodes[node.next].v;
            if (new_value != next_sum)
            {
                pop_node.value() = {node.v + nodes[node.next].v, i};
                set->insert(std::move(pop_node));
                continue;
            }

            num_bad += (new_value > next_next.v) + (prev.v > new_value) -
                       (prev.v > node.v) - (node.v > next.v) -
                       (next.v > next_next.v);

            i64 old_value = std::exchange(node.v, new_value);
            removed[node.next] = 1;
            node.next = next.next;
            next_next.prev = i;

            if (next.next != right_bound)
            {
                pop_node.value() = {node.v + next_next.v, i};
                set->insert(std::move(pop_node));
            }

            if (node.prev != left_bound)
            {
                i64 pv = prev.v;
                auto x = set->extract(set->find({pv + old_value, node.prev}));
                x.value().first = node.v + pv;
                set->insert(std::move(x));
            }

            ++r;
        }

        return r;
    }
};
