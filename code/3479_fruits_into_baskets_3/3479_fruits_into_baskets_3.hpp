#pragma once

#include <functional>
#include <span>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class SegmentTree
{
public:
    void Build(std::span<const int> data_)
    {
        data = data_;
        n = static_cast<u32>(data.size());
        BuildR(0, 0, n - 1);
    }

    void BuildR(u32 node, u32 l, u32 r)
    {
        if (l == r)
        {
            nodes[node] = data[l];
            return;
        }

        u32 mid = (l + r) / 2;
        BuildR(2 * node + 1, l, mid);
        BuildR(2 * node + 2, mid + 1, r);
        nodes[node] = std::max(nodes[2 * node + 1], nodes[2 * node + 2]);
    }

    void Update(u32 idx, int val) { UpdateR(idx, val, 0, 0, n - 1); }

    void UpdateR(u32 idx, int val, u32 node, u32 l, u32 r)
    {
        if (l == r)
        {
            nodes[node] = val;
            return;
        }

        u32 mid = (l + r) / 2;
        if (idx <= mid)
        {
            UpdateR(idx, val, 2 * node + 1, l, mid);
        }
        else
        {
            UpdateR(idx, val, 2 * node + 2, mid + 1, r);
        }

        nodes[node] = std::max(nodes[2 * node + 1], nodes[2 * node + 2]);
    }

    template <typename Cmp>
    u32 UpdateFirst(int search_val, const Cmp& cmp, int replace_val)
    {
        return UpdateFirst(search_val, cmp, replace_val, 0, 0, n - 1);
    }

    template <typename Cmp>
    u32 UpdateFirst(
        int search_val,
        const Cmp& cmp,
        int replace_val,
        u32 node,
        u32 l,
        u32 r)
    {
        if (!cmp(nodes[node], search_val)) return n;
        if (l == r)
        {
            nodes[node] = replace_val;
            return l;
        }

        u32 mid = (l + r) / 2;
        u32 idx =
            UpdateFirst(search_val, cmp, replace_val, 2 * node + 1, l, mid);
        if (idx == n)
        {
            idx = UpdateFirst(
                search_val,
                cmp,
                replace_val,
                2 * node + 2,
                mid + 1,
                r);
        }

        if (idx != n)
        {
            nodes[node] = std::max(nodes[2 * node + 1], nodes[2 * node + 2]);
        }

        return idx;
    }

    template <typename Cmp>
    u32 FindFirst(int val, const Cmp& cmp) const
    {
        return FindFirst(val, cmp, 0, 0, n - 1);
    }

    template <typename Cmp>
    u32 FindFirst(int val, const Cmp& cmp, u32 node, u32 l, u32 r) const
    {
        if (!cmp(nodes[node], val)) return n;
        if (l == r) return l;

        u32 mid = (l + r) / 2;

        if (u32 result = FindFirst(val, cmp, 2 * node + 1, l, mid); result != n)
        {
            return result;
        }

        return FindFirst(val, cmp, 2 * node + 2, mid + 1, r);
    }

    u32 n = 0;
    std::span<const int> data;
    std::array<int, 400'004> nodes{};
};

class Solution
{
public:
    [[nodiscard]] static constexpr size_t numOfUnplacedFruits(
        std::vector<int>& fruits,
        std::vector<int>& baskets)
    {
        static SegmentTree st;
        st.Build(baskets);

        size_t r = fruits.size();

        for (int f : fruits)
        {
            if (st.UpdateFirst(f, std::greater_equal{}, 0) != st.n)
            {
                --r;
            }
        }

        return r;
    }
};
