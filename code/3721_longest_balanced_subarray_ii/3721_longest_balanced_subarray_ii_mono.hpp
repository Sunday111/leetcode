#include <algorithm>
#include <bit>
#include <cstdint>
#include <optional>
#include <vector>



#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

[[nodiscard]] inline constexpr u32 num_required_nodes(u32 n) noexcept
{
    return (std::bit_ceil(n) << 1);
}

struct Interval
{
    u32 begin = 0;
    u32 end = 0;

    [[nodiscard]] FORCE_INLINE constexpr u32 size() const noexcept
    {
        return end - begin;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 mid() const noexcept
    {
        u32 mid = begin + size() / 2;
        return mid;
    }

    [[nodiscard]] FORCE_INLINE constexpr std::pair<Interval, Interval> split()
        const noexcept
    {
        u32 m = mid();
        return {{.begin = begin, .end = m}, {.begin = m, .end = end}};
    }

    [[nodiscard]] FORCE_INLINE constexpr bool contains(
        const Interval& interval) const noexcept
    {
        return begin <= interval.begin && end >= interval.end;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool disjoint(
        const Interval& interval) const noexcept
    {
        return end <= interval.begin || begin >= interval.end;
    }
};

class SegmentTree
{
public:
    struct Node
    {
        int lazy = 0;
        int min = 0;
        int max = 0;
    };

    Node* nodes{};
    Interval all{};

    constexpr explicit SegmentTree(Node* p, u32 n) noexcept
        : nodes(p),
          all{0, n}
    {
        std::fill_n(nodes, num_required_nodes(n), Node{0, 0, 0});
    }

    FORCE_INLINE constexpr void push(
        u32 node_id,
        Interval node_interval) noexcept
    {
        if (auto& node = nodes[node_id]; node.lazy && node_interval.size() != 1)
        {
            const u32 left_node_id = node_id * 2,
                      right_node_id = left_node_id + 1;

            auto& left = nodes[left_node_id];
            left.lazy += node.lazy;
            left.min += node.lazy;
            left.max += node.lazy;

            auto& right = nodes[right_node_id];
            right.lazy += node.lazy;
            right.min += node.lazy;
            right.max += node.lazy;

            node.lazy = 0;
        }
    }

    FORCE_INLINE constexpr void update(
        Interval change_interval,
        Interval node_interval,
        u32 node_id,
        int delta) noexcept
    {
        // No overlap
        if (change_interval.disjoint(node_interval)) return;

        auto& node = nodes[node_id];

        // Full overlap
        if (change_interval.contains(node_interval))
        {
            node.lazy += delta;
            node.min += delta;
            node.max += delta;
            return;
        }

        // Partial overlap, have to apply changes accumulated in lazy
        push(node_id, node_interval);

        // And then update children
        auto [l, r] = node_interval.split();
        const u32 left_node_id = node_id * 2, right_node_id = left_node_id + 1;
        update(change_interval, l, left_node_id, delta);
        update(change_interval, r, right_node_id, delta);
        node.min = std::min(nodes[left_node_id].min, nodes[right_node_id].min);
        node.max = std::max(nodes[left_node_id].max, nodes[right_node_id].max);
    }

    FORCE_INLINE constexpr void update(
        Interval change_interval,
        int delta) noexcept
    {
        update(change_interval, all, 1, delta);
    }

    constexpr int query(u32 idx, u32 node_id, Interval node_interval) noexcept
    {
        auto& node = nodes[node_id];
        if (node_interval.size() == 1) return node.lazy;
        push(node_id, node_interval);
        auto m = node_interval.mid();
        const u32 left_node_id = node_id * 2, right_node_id = left_node_id + 1;
        auto [l, r] = node_interval.split();
        if (idx < m) return query(idx, left_node_id, l);
        return query(idx, right_node_id, r);
    }
    constexpr int query(u32 idx) noexcept { return query(idx, 1, all); }

    FORCE_INLINE constexpr std::optional<u32> find_first(
        int value,
        Interval search_interval,
        u32 node_id,
        Interval node_interval) noexcept
    {
        if (node_interval.disjoint(search_interval)) return std::nullopt;

        auto& node = nodes[node_id];

        if (value < node.min || value > node.max) return std::nullopt;

        if (node_interval.size() == 1)
        {
            if (node.lazy == value) return node_interval.begin;
            return std::nullopt;
        }

        push(node_id, node_interval);
        auto [l, r] = node_interval.split();
        const u32 left_node_id = node_id * 2, right_node_id = left_node_id + 1;
        auto x = find_first(value, search_interval, left_node_id, l);
        if (!x) x = find_first(value, search_interval, right_node_id, r);
        return x;
    }

    FORCE_INLINE constexpr std::optional<u32> find_first(
        int value,
        Interval search_interval) noexcept
    {
        return find_first(value, search_interval, 1, all);
    }
};

class Solution
{
public:
    [[nodiscard]] u32 longestBalanced(std::vector<int>& nums) noexcept
    {
        static SegmentTree ::Node nodes[num_required_nodes(100'001)];
        SegmentTree st(nodes, static_cast<u32>(nums.size() + 1));

        auto [lo, hi] = std::ranges::minmax(nums);

        static u32 prev[100'000];
        std::ranges::fill_n(prev, (hi - lo) + 1, ~u32{});

        u32 r = 0;
        int b = 0;
        for (u32 i = 0; i != nums.size(); ++i)
        {
            int v = nums[i];
            auto& pv = prev[v - lo];
            int t = ((v & 1) << 1) - 1;
            b += -(pv == ~u32()) & t;
            if (pv != ~u32{})
            {
                st.update({pv, i}, -t);
            }
            pv = i;
            st.update({i, i + 1}, b);

            if (!b)
            {
                r = 1u + i;
                continue;
            }

            r = std::max<u32>(r, i - st.find_first(b, {0, i}).value_or(i));
        }

        return r;
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
