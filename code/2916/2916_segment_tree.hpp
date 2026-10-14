#include <algorithm>
#include <bit>
#include <vector>

#include "integral_aliases.hpp"
#include "sync_stdio.hpp"

template <typename Node, u32 max_n>
class SegmentTree
{
public:
    explicit SegmentTree(u32 n)
        : leaf_count(std::bit_ceil(n)),
          height(static_cast<u32>(std::countr_zero(leaf_count)))
    {
        std::fill_n(tree, 2 * leaf_count, Node{});
    }

    const Node& root() const { return tree[1]; }

    [[gnu::no_sanitize_address]]
    void update(u32 ql, u32 qr, const typename Node::Update& value)
    {
        u32 left = ql + leaf_count;
        u32 right = qr + leaf_count + 1;
        u32 left_path = left;
        u32 right_path = right;

        for (u32 level = height; level != 0; --level)
        {
            u32 child_len = 1u << (level - 1);
            if (((left >> level) << level) != left)
            {
                push(left >> level, child_len);
            }
            if (((right >> level) << level) != right)
            {
                push((right - 1) >> level, child_len);
            }
        }

        for (u32 len = 1; left < right; left >>= 1, right >>= 1, len <<= 1)
        {
            if (left & 1u) tree[left++].apply(value, len);
            if (right & 1u) tree[--right].apply(value, len);
        }

        for (u32 level = 1; level <= height; ++level)
        {
            if (((left_path >> level) << level) != left_path)
            {
                pull(left_path >> level);
            }
            if (((right_path >> level) << level) != right_path)
            {
                pull((right_path - 1) >> level);
            }
        }
    }

private:
    inline static Node tree[2 * std::bit_ceil(max_n)]{};
    u32 leaf_count;
    u32 height;

    [[gnu::no_sanitize_address]]
    void push(u32 node, u32 child_len)
    {
        tree[node]
            .push(tree[node * 2], tree[node * 2 + 1], child_len, child_len);
    }

    [[gnu::no_sanitize_address]]
    void pull(u32 node)
    {
        tree[node].pull(tree[node * 2], tree[node * 2 + 1]);
    }
};

struct SumSquaresNode
{
    using Update = u32;
    static constexpr u32 mod = 1'000'000'007;

    u32 sum = 0;
    u32 sq = 0;
    u32 lazy = 0;

    [[gnu::no_sanitize_address]]
    void apply(Update value, u32 len)
    {
        u64 v = value;
        sq = (sq + 2 * v * sum + v * v * len) % mod;
        sum = (sum + v * len) % mod;
        lazy += value;
    }

    [[gnu::no_sanitize_address]]
    void push(
        SumSquaresNode& left,
        SumSquaresNode& right,
        u32 left_len,
        u32 right_len)
    {
        if (lazy == 0) return;
        left.apply(lazy, left_len);
        right.apply(lazy, right_len);
        lazy = 0;
    }

    [[gnu::no_sanitize_address]]
    void pull(const SumSquaresNode& left, const SumSquaresNode& right)
    {
        sum = (left.sum + right.sum) % mod;
        sq = (left.sq + right.sq) % mod;
    }
};

class SegmentTreeSolution
{
    static constexpr u32 max_n = 100'000;
    static constexpr u32 max_value = 100'000;
    inline static u32 last[max_value + 1]{};

public:
    u32 sumCounts(std::vector<int>& input)
    {
        auto nums = reinterpret_cast<const u32*>(input.data());
        u32 n = static_cast<u32>(input.size());

        SegmentTree<SumSquaresNode, max_n> tree(n);

        std::fill_n(last, max_value + 1, u32{0});

        u64 ans = 0;

        for (u32 r = 0; r < n; r++)
        {
            u32 ql = last[nums[r]];

            tree.update(ql, r, 1);

            ans = (ans + tree.root().sq) % SumSquaresNode::mod;

            last[nums[r]] = r + 1;
        }

        return static_cast<u32>(ans);
    }
};
