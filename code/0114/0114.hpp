#include <array>
#include <utility>

#include "binary_tree/lc_tree_node.hpp"

class Solution
{
public:
    void flatten(TreeNode* root)
    {
        auto x = root;
        while (x)
        {
            if (x->left)
            {
                if (x->right)
                {
                    auto t = x->left;
                    while (t->right || t->left)
                    {
                        t = std::array{t->right, t->left}[!t->right];
                    }
                    t->right = x->right;
                    x->right = nullptr;
                }

                std::swap(x->left, x->right);
            }
            x = x->right;
        }
    }
};
