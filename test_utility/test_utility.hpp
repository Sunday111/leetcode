#pragma once

#include <cassert>
#include <optional>
#include <queue>
#include <span>
#include <sstream>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
template <typename BinaryTreeNode>
bool CompareBinaryTrees(BinaryTreeNode* root_a, BinaryTreeNode* root_b)
{
    std::queue<std::pair<BinaryTreeNode*, BinaryTreeNode*>> q{{root_a, root_b}};

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        if (static_cast<bool>(a) ^ static_cast<bool>(b)) return false;
        if (!a) continue;
        if (a->val != b->val) return false;

        q.emplace(a->left, b->left);
        q.emplace(a->right, b->right);
    }

    return true;
}

template <typename BinaryTreeNode>
struct LeetCodeBinaryTree
{
    std::deque<BinaryTreeNode> nodes;
    std::vector<uint64_t> free_nodes;
    BinaryTreeNode* root = nullptr;

    [[nodiscard]] static LeetCodeBinaryTree FromArray(
        std::span<std::optional<int>> values)
    {
        LeetCodeBinaryTree<BinaryTreeNode> tree;

        assert(!values.empty());
        assert(values.front().has_value());

        tree.root = &tree.nodes.emplace_back(BinaryTreeNode{*values.front()});
        std::vector<std::pair<BinaryTreeNode*, size_t>> queue{
            {tree.root, 0},
        };

        while (!queue.empty())
        {
            auto [node, iroot] = queue.back();
            queue.pop_back();

            if (size_t ileft = iroot * 2 + 1; ileft < values.size())
            {
                if (const auto& opt = values[ileft])
                {
                    node->left = &tree.nodes.emplace_back(BinaryTreeNode{*opt});
                    queue.push_back({node->left, ileft});
                }
            }

            if (size_t iright = iroot * 2 + 2; iright < values.size())
            {
                if (const auto& opt = values[iright])
                {
                    node->right =
                        &tree.nodes.emplace_back(BinaryTreeNode{*opt});
                    queue.push_back({node->right, iright});
                }
            }
        }

        return tree;
    }

    [[nodiscard]] static std::vector<std::optional<int>> StringToArray(
        std::string_view str)
    {
        std::stringstream stream(std::string{str});
        std::vector<std::optional<int>> r;

        while (!stream.eof())
        {
            if (int c = stream.peek(); std::isdigit(c) || c == '-')
            {
                int value{};
                stream >> value;
                r.push_back(value);
            }
            else
            {
                int c0 = stream.get();
                int c1 = stream.get();
                int c2 = stream.get();
                int c3 = stream.get();

                assert(c0 == 'n');
                assert(c1 == 'u');
                assert(c2 == 'l');
                assert(c3 == 'l');

                r.push_back(std::nullopt);
            }

            if (int p = stream.peek(); p == ',') stream.get();
        }

        return r;
    }

    [[nodiscard]] static LeetCodeBinaryTree FromString(std::string_view str)
    {
        auto array = StringToArray(str);
        return FromArray(array);
    }
};
