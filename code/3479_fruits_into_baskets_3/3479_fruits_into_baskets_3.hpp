#pragma once

#include <functional>
#include <span>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define HOT_PATH __attribute__((hot))

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
    FORCE_INLINE constexpr void Build(std::span<const int> data_) noexcept
    {
        data = data_;
        n = static_cast<u32>(data.size());
        BuildR(0, 0, n - 1);
    }

    constexpr void BuildR(u32 node, u32 l, u32 r) noexcept
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

    FORCE_INLINE constexpr void Update(u32 idx, int val) noexcept
    {
        // Leaf node index in the segment tree array
        u32 node = 0, l = 0, r = n - 1;

        // Find the leaf corresponding to idx iteratively
        while (l != r)
        {
            u32 mid = (l + r) / 2;
            if (idx <= mid)
            {
                node = 2 * node + 1;
                r = mid;
            }
            else
            {
                node = 2 * node + 2;
                l = mid + 1;
            }
        }

        // Update leaf value
        nodes[node] = val;

        // Move up and update parents
        while (node != 0)
        {
            node = (node - 1) / 2;
            nodes[node] = std::max(nodes[2 * node + 1], nodes[2 * node + 2]);
        }
    }

    template <typename Cmp>
    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32
    UpdateFirst(int val, const Cmp& cmp, int replace_val) noexcept
    {
        u32 node = 0, l = 0, r = n - 1;

        if (!cmp(nodes[node], val)) return n;  // no candidate

        // Traverse down the tree
        while (l != r)
        {
            u32 mid = (l + r) / 2;

            if (cmp(nodes[2 * node + 1], val))
            {
                // Go left
                node = 2 * node + 1;
                r = mid;
            }
            else
            {
                // Go right
                node = 2 * node + 2;
                l = mid + 1;
            }
        }

        // Now at leaf node, update
        nodes[node] = replace_val;

        // Go back up and fix parents
        while (node != 0)
        {
            node = (node - 1) / 2;
            nodes[node] = std::max(nodes[2 * node + 1], nodes[2 * node + 2]);
        }

        return l;
    }

    template <typename Cmp>
    [[nodiscard]] FORCE_INLINE constexpr u32 FindFirst(int val, const Cmp& cmp)
        const noexcept
    {
        u32 node = 0, l = 0, r = n - 1;

        if (!cmp(nodes[node], val)) return n;

        while (l != r)
        {
            u32 mid = (l + r) / 2;

            if (cmp(nodes[2 * node + 1], val))
            {
                node = 2 * node + 1;
                r = mid;
            }
            else
            {
                node = 2 * node + 2;
                l = mid + 1;
            }
        }

        return l;
    }

    u32 n = 0;
    std::span<const int> data;
    std::array<int, 400'004> nodes{};
};

class Solution
{
public:
    [[nodiscard]] static size_t numOfUnplacedFruits(
        std::vector<int>& fruits,
        std::vector<int>& baskets) noexcept
    {
        static SegmentTree st;
        st.Build(baskets);

        size_t r = 0;

        for (int f : fruits)
        {
            r += (st.UpdateFirst(f, std::greater_equal{}, 0) == st.n);
        }

        return r;
    }
};
