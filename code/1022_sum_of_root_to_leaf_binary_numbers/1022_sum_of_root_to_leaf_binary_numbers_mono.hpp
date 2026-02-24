#include <cstdint>



#ifdef LC_LOCAL_BUILD

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x),
          left(left),
          right(right)
    {
    }
};

#endif

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 sumRootToLeaf(
        TreeNode* x,
        u32 p = 0) noexcept
    {
        if (!x) return 0;

        p <<= 1;
        p |= (x->val & 1);

        bool leaf = !x->left && !x->right;
        return (p & -u32{leaf}) + sumRootToLeaf(x->left, p) +
               sumRootToLeaf(x->right, p);
    }
};
