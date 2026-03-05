#include <vector>

#include "force_inline.hpp"
#include "lc_tree_node.hpp"
#include "pyramid_bitset.hpp"

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
            if (!initialized.get(id))
            {
                initialized.add(id);
                roots.add(id);
                x = TreeNode{static_cast<int>(id)};
            }
            return x;
        };

        for (auto& descr : descriptions)
        {
            u32 pid = cast<u32>(descr[0]), cid = cast<u32>(descr[1]);
            auto& parent = get_node(pid);
            *(descr[2] ? &parent.left : &parent.right) = &get_node(cid);
            roots.remove(cid);
        }

        return &nodes[roots.min()];
    }
};
