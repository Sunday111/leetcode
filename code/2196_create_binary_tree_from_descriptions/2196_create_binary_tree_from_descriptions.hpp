#include <vector>

#include "binary_tree/lc_tree_node.hpp"
#include "cast.hpp"
#include "force_inline.hpp"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_get.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

class Solution
{
public:
    [[nodiscard]] TreeNode* createBinaryTree(
        const std::vector<std::vector<int>>& descriptions)
    {
        static TreeNode nodes[100001];
        PyramidBitset<100001> initialized, roots;

        auto get_node = [&](u32 id) INLINE_LAMBDA -> TreeNode&
        {
            auto& x = nodes[id];
            if (!pbs_get(initialized, id))
            {
                pbs_add(initialized, id);
                pbs_add(roots, id);
                x = TreeNode{static_cast<int>(id)};
            }
            return x;
        };

        for (auto& descr : descriptions)
        {
            u32 pid = cast<u32>(descr[0]), cid = cast<u32>(descr[1]);
            auto& parent = get_node(pid);
            *(descr[2] ? &parent.left : &parent.right) = &get_node(cid);
            pbs_remove(roots, cid);
        }

        return &nodes[pbs_min(roots)];
    }
};
