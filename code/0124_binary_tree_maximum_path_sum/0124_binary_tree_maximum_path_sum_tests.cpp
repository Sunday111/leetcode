#include <cassert>
#include <deque>
#include <sstream>

#include "0124_binary_tree_maximum_path_sum.hpp"
#include "gtest/gtest.h"

struct Tree
{
    std::deque<TreeNode> nodes;
    std::vector<uint64_t> free_nodes;
    TreeNode* root = nullptr;

    [[nodiscard]] static Tree FromArray(std::span<std::optional<int>> values)
    {
        Tree tree;

        assert(!values.empty());
        assert(values.front().has_value());

        tree.root = &tree.nodes.emplace_back(TreeNode{*values.front()});
        std::vector<std::pair<TreeNode*, size_t>> queue{
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
                    node->left = &tree.nodes.emplace_back(TreeNode{*opt});
                    queue.push_back({node->left, ileft});
                }
            }

            if (size_t iright = iroot * 2 + 2; iright < values.size())
            {
                if (const auto& opt = values[iright])
                {
                    node->right = &tree.nodes.emplace_back(TreeNode{*opt});
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

    [[nodiscard]] static Tree FromString(std::string_view str)
    {
        auto array = StringToArray(str);
        return FromArray(array);
    }
};

TEST(t0124_binary_tree_maximum_path_sum, test_1)
{
    Solution s{};

    auto tree = Tree::FromString("1,2,3");
    ASSERT_EQ(s.maxPathSum(tree.root), 6);
}

TEST(t0124_binary_tree_maximum_path_sum, test_2)
{
    Solution s{};

    auto tree = Tree::FromString("-10,9,20,null,null,15,7");
    ASSERT_EQ(s.maxPathSum(tree.root), 42);
}

TEST(t0124_binary_tree_maximum_path_sum, test_3)
{
    Solution s{};

    auto tree = Tree::FromString("-2,-1");
    ASSERT_EQ(s.maxPathSum(tree.root), -1);
}
