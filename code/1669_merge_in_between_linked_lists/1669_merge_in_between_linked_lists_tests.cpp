#include "1669_merge_in_between_linked_lists.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"

TEST(t1669_merge_in_between_linked_lists, test_1)
{
    auto l1 = LeetCodeList<ListNode>::FromString("[10,1,13,6,9,5]");
    auto l2 = LeetCodeList<ListNode>::FromString("[1000000,1000001,1000002]");
    int a = 3, b = 4;

    std::string_view expected = "[10,1,13,1000000,1000001,1000002,5]";
    auto actual =
        ListToString(Solution{}.mergeInBetween(l1.head, a, b, l2.head));
    ASSERT_EQ(expected, actual);
}

TEST(t1669_merge_in_between_linked_lists, test_2)
{
    auto l1 = LeetCodeList<ListNode>::FromString("[0,1,2,3,4,5,6]");
    auto l2 = LeetCodeList<ListNode>::FromString(
        "[1000000,1000001,1000002,1000003,1000004]");
    int a = 2, b = 5;

    std::string_view expected =
        "[0,1,1000000,1000001,1000002,1000003,1000004,6]";
    auto actual =
        ListToString(Solution{}.mergeInBetween(l1.head, a, b, l2.head));
    ASSERT_EQ(expected, actual);
}
