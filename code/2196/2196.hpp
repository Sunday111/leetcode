#include <bit>
#include <utility>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "lc_tree_node.hpp"
#include "ptr_if.hpp"

class Solution
{
    inline static TreeNode nodes[100001];

    inline static const auto node_numbers_init = []
    {
        // Init val only once
        for (u32 i = 0; TreeNode& node : nodes) node.val = cast<int>(i++);
        return 'a';
    }();

public:
    [[nodiscard]] TreeNode* createBinaryTree(
        const std::vector<std::vector<int>>& descriptions)
    {
        constexpr u32 nw = (100'001 / 64) + 1;
        static u64 roots[nw], init[nw];

        auto set_bit = [] [[gnu::always_inline]] (
                           u64 * words,
                           u32 i,
                           bool condition = true) noexcept
        {
            words[i >> 6] |= (u64{condition} << (i & 63));
        };

        auto get_bit = [] [[nodiscard, gnu::always_inline]] (
                           const u64* words,
                           u32 i) noexcept -> bool
        {
            return words[i >> 6] & (u64{1} << (i & 63));
        };

        auto clear_bit = [] [[gnu::always_inline]]
                         (u64 * words, u32 i, bool condition = true) noexcept
        {
            words[i >> 6] &= ~(u64{condition} << (i & 63));
        };

        for (auto& descr : descriptions)
        {
            u32 p_id = cast<u32>(descr[0]), c_id = cast<u32>(descr[1]);
            auto &p = nodes[p_id], &c = nodes[c_id];
            bool p_new = !get_bit(init, p_id), c_new = !get_bit(init, c_id);
            set_bit(init, p_id), set_bit(init, c_id);
            set_bit(roots, p_id, p_new);
            clear_bit(roots, c_id);
            c.left = ptrif<TreeNode*>(c_new, nullptr, c.left);
            c.right = ptrif<TreeNode*>(c_new, nullptr, c.right);
            TreeNode** t[2]{&p.right, &p.left};
            *t[descr[2]] = &c;
            *t[!descr[2]] = ptrif<TreeNode*>(p_new, nullptr, *t[!descr[2]]);
        }

        u32 ri = 0;
        for (u32 wi = 0; wi != nw; ++wi)
        {
            init[wi] = 0;
            u64 w = std::exchange(roots[wi], 0);
            bool has_bit = w != 0;
            u32 bit_index = (wi << 6) | cast<u32>(std::countr_zero(w));
            ri = std::max(ri, bit_index & -u32{has_bit});
        }

        return &nodes[ri];
    }
};

#include "sync_stdio.hpp"
