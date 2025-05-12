#include <cassert>

#include "0019_remove_nth_node_from_end_of_list.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"

using List = LeetCodeList<ListNode>;

TEST(t0019_remove_nth_node_from_end_of_list, test_1)
{
    auto in_list = List::FromString("1,2,3,4,5");
    constexpr int n = 2;
    auto expected = List::FromString("1,2,3,5");
    auto actual = Solution{}.removeNthFromEnd(in_list.head, n);
    ASSERT_TRUE(CompareLists(expected.head, actual));
}
