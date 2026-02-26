#include "0237_delete_node_in_a_linked_list.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"

TEST(t0237_delete_node_in_a_linked_list, test_1)
{
    auto orig = LeetCodeList<ListNode>::FromString("[4,5,1,9]");
    int remove_value = 5;
    std::string_view expected = "[4,1,9]";

    auto node_to_delete = FindFirst(orig.head, remove_value);
    ASSERT_NE(node_to_delete, nullptr);
    ASSERT_NE(node_to_delete->next, nullptr);

    Solution{}.deleteNode(node_to_delete);

    ASSERT_EQ(expected, ListToString(orig.head));
}

TEST(t0237_delete_node_in_a_linked_list, test_2)
{
    auto orig = LeetCodeList<ListNode>::FromString("[4,5,1,9]");
    int remove_value = 1;
    std::string_view expected = "[4,5,9]";

    auto node_to_delete = FindFirst(orig.head, remove_value);
    ASSERT_NE(node_to_delete, nullptr);
    ASSERT_NE(node_to_delete->next, nullptr);

    Solution{}.deleteNode(node_to_delete);

    ASSERT_EQ(expected, ListToString(orig.head));
}
