#include <array>
#include <utility>

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
                    t->right = std::exchange(x->right, nullptr);
                }

                std::swap(x->left, x->right);
            }
            x = x->right;
        }
    }
};
