#include "gtest/gtest.h"
#include "lc_tree_node.hpp"
#include "leet_code_binary_tree.hpp"
#include "leet_code_list.hpp"
#include "singly_linked_list/ll_node.hpp"
#include "test_cases_helpers.hpp"

TEST(LeetCodeContainers, ListCopiesOwnTheirNodes)
{
    using List = LeetCodeList<ListNode>;
    List copy;
    {
        auto original = List::FromString("[1,2,3]");
        auto constructed = original;
        ASSERT_NE(constructed.head, original.head);
        constructed.head->next->val = 4;
        EXPECT_EQ(original.head->next->val, 2);
        copy = constructed;
        ASSERT_NE(copy.head, constructed.head);
    }
    EXPECT_EQ(ListToString(copy.head), "[1,4,3]");
}

TEST(LeetCodeContainers, TreeCopiesOwnTheirNodes)
{
    using Tree = LeetCodeBinaryTree<TreeNode>;
    Tree copy;
    {
        auto original = Tree::FromString("1,2,3,null,4");
        auto constructed = original;
        ASSERT_NE(constructed.root, original.root);
        constructed.root->left->right->val = 5;
        EXPECT_EQ(original.root->left->right->val, 4);
        copy = constructed;
        ASSERT_NE(copy.root, constructed.root);
    }
    EXPECT_EQ(Tree::ToString(copy.root), "[1,2,3,null,5]");
}

TEST(LeetCodeContainers, EmptyCopies)
{
    LeetCodeList<ListNode> list;
    auto list_copy = list;
    list_copy = list;
    EXPECT_EQ(list_copy.head, nullptr);
    EXPECT_TRUE(list_copy.nodes.empty());

    LeetCodeBinaryTree<TreeNode> tree;
    auto tree_copy = tree;
    tree_copy = tree;
    EXPECT_EQ(tree_copy.root, nullptr);
    EXPECT_TRUE(tree_copy.nodes.empty());
}

TEST(LeetCodeContainers, ParsedCasesSurviveVectorGrowth)
{
    using List = LeetCodeList<ListNode>;
    auto lists = parse_test_cases_with_types<std::tuple<List>, int>(
        "[1,2,3] 0 [4,5] 0 [6] 0");
    EXPECT_EQ(ListToString(std::get<0>(std::get<0>(lists[0])).head), "[1,2,3]");
    EXPECT_EQ(ListToString(std::get<0>(std::get<0>(lists[1])).head), "[4,5]");

    using Tree = LeetCodeBinaryTree<TreeNode>;
    auto trees = parse_test_cases_with_types<std::tuple<Tree>, int>(
        "[1,2,3,null,4] 0 [5,6] 0 [7] 0");
    EXPECT_EQ(
        Tree::ToString(std::get<0>(std::get<0>(trees[0])).root),
        "[1,2,3,null,4]");
    EXPECT_EQ(Tree::ToString(std::get<0>(std::get<0>(trees[1])).root), "[5,6]");
}
