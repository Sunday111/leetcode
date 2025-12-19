#include <array>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode *left, *right;
};

using u8 = uint8_t;
using u16 = uint16_t;

class Solution
{
public:
    inline static std::array<std::vector<TreeNode*>, 256> memo;

    const std::vector<TreeNode*>& generateTrees(u8 n, u8 s = 1) noexcept
    {
        auto& out = memo[((n << 4) | s) & 0xff];

        if (out.empty())
        {
            if (n < s)
            {
                out = {nullptr};
            }
            else
            {
                for (u8 root = s; root <= n; ++root)
                {
                    for (auto l : generateTrees(root - 1, s))
                    {
                        for (auto r : generateTrees(n, root + 1))
                        {
                            out.push_back(new TreeNode{root, l, r});  // NOLINT
                        }
                    }
                }
            }
        }

        return out;
    }
};
