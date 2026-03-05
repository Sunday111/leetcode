#include <vector>

#include "force_inline.hpp"
#include "lc_tree_node.hpp"
#include "pyramid_bitset.hpp"

class Solution
{
public:
    struct NodeInfo
    {
        TreeNode node{};
        bool is_root = true;
    };

    [[nodiscard]] TreeNode* createBinaryTree(
        const std::vector<std::vector<int>>& descriptions)
    {
        static NodeInfo nodes[100001];

        PyramidBitset<100001> used;

        auto get_node = [&](u32 id) INLINE_LAMBDA -> NodeInfo&
        {
            auto& x = nodes[id];
            if (!used.get(id))
            {
                used.add(id);
                x.node = TreeNode{static_cast<int>(id)};
                x.is_root = true;
            }
            return x;
        };

        for (auto& descr : descriptions)
        {
            u32 parent_id = static_cast<u32>(descr[0]);
            u32 child_id = static_cast<u32>(descr[1]);
            bool is_left = descr[2];

            auto& parent_info = get_node(parent_id);
            auto& parent = parent_info.node;
            auto& child_info = get_node(child_id);
            auto& child = child_info.node;

            *(is_left ? &parent.left : &parent.right) = &child;

            child_info.is_root = false;
        }

        while (true)
        {
            u32 id = used.min();
            auto& x = nodes[id];
            if (x.is_root) return &x.node;
            used.remove(id);
        }

        std::unreachable();
    }
};
