#include "lc_tree_node.hpp"

class Solution
{
public:
    int v;
    bool isUnivalTreeR(TreeNode* root)
    {
        if (root)
        {
            if (root->val != v) return false;
            if (!isUnivalTreeR(root->left)) return false;
            if (!isUnivalTreeR(root->right)) return false;
        }

        return true;
    }
    bool isUnivalTree(TreeNode* root)
    {
        v = root->val;
        return isUnivalTreeR(root);
    }
};
