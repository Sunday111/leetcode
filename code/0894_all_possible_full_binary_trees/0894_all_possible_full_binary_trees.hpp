#include <unordered_map>
#include <vector>

#include "lc_tree_node.hpp"
class Solution
{
public:
    std::unordered_map<int, std::vector<TreeNode*>> memo = {
        {0, {}},
        {1, {new TreeNode{}}},
    };

    std::vector<TreeNode*>& dfs(int n)
    {
        auto [it, added] = memo.try_emplace(n);
        if (added)
        {
            for (int right = n - 2, left = 1; right; ++left, --right)
            {
                auto& dr = dfs(right);
                for (auto l : dfs(left))
                {
                    for (auto r : dr)
                    {
                        // NOLINTNEXTLINE
                        it->second.emplace_back(new TreeNode{0, l, r});
                    }
                }
            }
        }
        return it->second;
    }

    auto allPossibleFBT(int n) { return std::move(dfs(n)); }
};
