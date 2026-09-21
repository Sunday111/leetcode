#include <initializer_list>

#include "lc_tree_node.hpp"

struct Frame
{
    const TreeNode* x{};
    int parent{}, s{}, c{};
};

class Solution
{
public:
    // One sentinel and one spare slot for unconditional child writes.
    inline static Frame st[100'002];

    int averageOfSubtree(const TreeNode* root) noexcept
    {
        int top = root != nullptr, r = 0;

        st[0] = {};
        st[1] = {root};

        for (int i = 1; i <= top; ++i)
        {
            Frame& f = st[i];
            f.s = f.x->val;
            f.c = 1;

            for (const auto* child : {f.x->left, f.x->right})
            {
                st[top + 1] = {child, i};
                top += !!child;
            }
        }

        while (top)
        {
            const auto& [x, parent, s, c] = st[top--];
            r += s / c == x->val;
            st[parent].s += s;
            st[parent].c += c;
        }

        return r;
    }
};
