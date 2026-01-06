#include <algorithm>
#include <string>

#include "lc_tree_node.hpp"

class Solution
{
public:
    void dfs(TreeNode* root, std::string& out)
    {
        if (!root) return;

        out += static_cast<char>(root->val + 'a');

        auto s0 = static_cast<uint16_t>(out.size());
        dfs(root->left, out);
        auto s1 = static_cast<uint16_t>(out.size());
        dfs(root->right, out);
        if (!(root->left && root->right)) return;

        const bool keep_left = [&]()
        {
            std::string_view full{out};
            auto base = full.substr(0, s0);
            auto left = full.substr(s0, s1 - s0);
            auto right = full.substr(s1, out.size() - s1);

            size_t n = std::min(left.size(), right.size()) + base.size();

            auto take_char = [&](size_t i, const auto& v) -> char
            {
                if (i < v.size())
                {
                    return *std::next(v.rbegin(), std::bit_cast<int64_t>(i));
                }

                i -= v.size();
                if (i < s0)
                {
                    return *std::next(base.rbegin(), std::bit_cast<int64_t>(i));
                }

                return 0;
            };

            for (size_t i = 0; i != n; ++i)
            {
                auto cl = take_char(i, left);
                auto cr = take_char(i, right);
                if (cl != cr) return cl < cr;
            }

            return left.size() < right.size();
        }();

        if (keep_left)
        {
            out.resize(s1);
        }
        else
        {
            out.erase(
                std::next(out.begin(), std::bit_cast<int16_t>(s0)),
                std::next(out.begin(), std::bit_cast<int16_t>(s1)));
        }
    }

    std::string smallestFromLeaf(TreeNode* root)
    {
        std::string r;
        r.reserve(24);
        dfs(root, r);
        std::ranges::reverse(r);
        return r;
    }
};
