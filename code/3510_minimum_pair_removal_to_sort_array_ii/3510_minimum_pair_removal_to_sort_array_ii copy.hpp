#include <algorithm>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

using u32 = uint32_t;
using u64 = uint64_t;
using i64 = int64_t;

struct HeapEntry
{
    static constexpr HeapEntry make(i64 s, u32 i) noexcept
    {
        const bool neg = s < 0;
        const u64 mag = std::bit_cast<u64>(neg ? -s : s);

        return {
            .sign = neg,
            .sum = mag,  // must fit in 47 bits!
            .idx = i,
        };
    }

    constexpr i64 get_sum() const noexcept
    {
        return std::bit_cast<i64>(sign ? -sum : sum);
    }

    u64 sign : 1;
    u64 sum : 47;
    u64 idx : 16;
};

static_assert(HeapEntry::make(2, 232).get_sum() == 2);
static_assert(HeapEntry::make(0, 232).get_sum() == 0);
static_assert(HeapEntry::make(-1, 232).get_sum() == -1);
static_assert(HeapEntry::make(-2, 232).get_sum() == -2);

class Solution
{
public:
    struct Node
    {
        i64 v = 0;
        u32 prev : 31 = 0;
        u32 bad : 1 = 0;
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
        u32 num_bad = 0;
        for (u32 i = 1; i != n; ++i)
        {
            long vi = nodes[i].v, vj = nodes[i + 1].v;
            num_bad += (nodes[i].bad = vi > vj);
            heap[hs++] = {vi + vj, i};
        }

        constexpr auto heap_cmp = std::greater{};

        std::ranges::make_heap(heap, heap + hs, heap_cmp);

        auto push = [&]() INLINE_LAMBDA
        {
            std::ranges::push_heap(heap, heap + hs, heap_cmp);
        };

        auto pop = [&]() INLINE_LAMBDA
        {
            std::ranges::pop_heap(heap, heap + hs, heap_cmp);
        };

        auto mark = [&](u32 i, bool v) INLINE_LAMBDA
        {
            num_bad -= nodes[i].bad;
            num_bad += (nodes[i].bad = v);
        };

        auto check_node = [&](u32 i) INLINE_LAMBDA
        {
            auto& curr = nodes[i];
            mark(i, curr.v > nodes[curr.next].v);
        };

        while (num_bad)
        {
            pop();
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
                push();
                continue;
            }

            ++r;
            node.v = s;

            u32 removed = node.next;
            node.next = nodes[node.next].next;

            nodes[node.next].prev = i;
            nodes[removed].removed = true;

            if (node.next != right_bound)
            {
                heap[hs - 1] = {node.v + nodes[node.next].v, i};
                push();
            }
            else
            {
                --hs;
            }

            if (node.prev != left_bound)
            {
                heap[hs++] = {node.v + nodes[node.prev].v, u32{node.prev}};
                push();
            }

            check_node(i);
            check_node(node.prev);
            mark(removed, false);
        }

        return r;
    }
};
