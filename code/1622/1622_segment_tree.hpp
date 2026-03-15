#include <algorithm>
#include <bit>

#include "mod_int.hpp"

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

[[nodiscard]] inline constexpr u32 num_required_nodes(u32 n) noexcept
{
    return (std::bit_ceil(n) << 1);
}

class SegmentTree
{
public:
    struct Node
    {
        ModInt mul;
        ModInt add;
    };

    static constexpr u32 kNumNodes = num_required_nodes(100'003);
    inline static Node nodes[kNumNodes];

    static constexpr Interval all{0, 100'003};

    constexpr explicit SegmentTree() noexcept
    {
        std::ranges::fill(nodes, Node{{1}, {0}});
    }

    FORCE_INLINE static constexpr void
    node_mul_add(Node& node, ModInt m, ModInt a)
    {
        // node.mul * (x * m + a) + node.add
        // node.mul * m * x + node.add + node.mul * a
        node.add = node.add * m + a;
        node.mul *= m;
    }

    FORCE_INLINE static constexpr void node_mul(Node& node, ModInt m)
    {
        node.add *= m;
        node.mul *= m;
    }

    FORCE_INLINE static constexpr void node_add(Node& node, ModInt a)
    {
        node.add = node.add + a;
    }

    FORCE_INLINE constexpr void push(
        u32 node_id,
        Interval node_interval) noexcept
    {
        if (auto& node = nodes[node_id];
            (node.mul.value != 1 || node.add.value != 0) &&
            node_interval.size() != 1)
        {
            const u32 left_node_id = node_id * 2,
                      right_node_id = left_node_id + 1;

            auto& left = nodes[left_node_id];
            node_mul_add(left, node.mul, node.add);

            auto& right = nodes[right_node_id];
            node_mul_add(right, node.mul, node.add);

            node.mul = {1};
            node.add = {0};
        }
    }

    FORCE_INLINE constexpr void update(
        Interval change_interval,
        Interval node_interval,
        u32 node_id,
        ModInt mul,
        ModInt add) noexcept
    {
        // No overlap
        if (change_interval.disjoint(node_interval)) return;

        auto& node = nodes[node_id];

        // Full overlap
        if (change_interval.contains(node_interval))
        {
            node_mul_add(node, mul, add);
            return;
        }

        // Partial overlap, have to apply changes accumulated in lazy
        push(node_id, node_interval);

        // And then update children
        auto [l, r] = node_interval.split();
        const u32 left_node_id = node_id * 2, right_node_id = left_node_id + 1;
        update(change_interval, l, left_node_id, mul, add);
        update(change_interval, r, right_node_id, mul, add);
    }

    FORCE_INLINE constexpr void
    update(Interval change_interval, ModInt mul, ModInt add) noexcept
    {
        update(change_interval, all, 1, mul, add);
    }

    FORCE_INLINE constexpr void update_mul(
        Interval change_interval,
        Interval node_interval,
        u32 node_id,
        ModInt mul) noexcept
    {
        // No overlap
        if (change_interval.disjoint(node_interval)) return;

        auto& node = nodes[node_id];

        // Full overlap
        if (change_interval.contains(node_interval))
        {
            node_mul(node, mul);
            return;
        }

        // Partial overlap, have to apply changes accumulated in lazy
        push(node_id, node_interval);

        // And then update children
        auto [l, r] = node_interval.split();
        const u32 left_node_id = node_id * 2, right_node_id = left_node_id + 1;
        update_mul(change_interval, l, left_node_id, mul);
        update_mul(change_interval, r, right_node_id, mul);
    }

    FORCE_INLINE constexpr void update_mul(
        Interval change_interval,
        ModInt mul) noexcept
    {
        update_mul(change_interval, all, 1, mul);
    }

    FORCE_INLINE constexpr void update_add(
        Interval change_interval,
        Interval node_interval,
        u32 node_id,
        ModInt add) noexcept
    {
        // No overlap
        if (change_interval.disjoint(node_interval)) return;

        auto& node = nodes[node_id];

        // Full overlap
        if (change_interval.contains(node_interval))
        {
            node_add(node, add);
            return;
        }

        // Partial overlap, have to apply changes accumulated in lazy
        push(node_id, node_interval);

        // And then update children
        auto [l, r] = node_interval.split();
        const u32 left_node_id = node_id * 2, right_node_id = left_node_id + 1;
        update_add(change_interval, l, left_node_id, add);
        update_add(change_interval, r, right_node_id, add);
    }

    FORCE_INLINE constexpr void update_add(
        Interval change_interval,
        ModInt add) noexcept
    {
        update_add(change_interval, all, 1, add);
    }

    constexpr ModInt
    query(u32 idx, u32 node_id, Interval node_interval) noexcept
    {
        auto& node = nodes[node_id];
        if (node_interval.size() == 1) return node.add;
        push(node_id, node_interval);
        auto m = node_interval.mid();
        const u32 left_node_id = node_id * 2, right_node_id = left_node_id + 1;
        auto [l, r] = node_interval.split();
        if (idx < m) return query(idx, left_node_id, l);
        return query(idx, right_node_id, r);
    }

    constexpr ModInt query(u32 idx) noexcept { return query(idx, 1, all); }
};

class Fancy
{
public:
    SegmentTree st;
    Interval interval{0, 0};

    void append(int x)
    {
        st.update_add({interval.end, interval.end + 1}, {static_cast<u32>(x)});
        ++interval.end;
    }

    void addAll(int x) { st.update_add(interval, {static_cast<u32>(x)}); }

    void multAll(int x) { st.update_mul(interval, {static_cast<u32>(x)}); }

    int getIndex(int x)
    {
        u32 i = static_cast<u32>(x);
        if (i >= interval.end) return -1;
        return static_cast<int>(st.query(i).value);
    }
};
