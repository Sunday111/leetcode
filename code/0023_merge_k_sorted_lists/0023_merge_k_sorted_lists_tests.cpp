#include "0023_merge_k_sorted_lists.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"

using List = LeetCodeList<ListNode>;

TEST(t0023_merge_k_sorted_lists, test_1)
{
    std::vector<std::string> inputs{"1,4,5", "1,3,4", "2,6"};
    auto input_lists = std::ranges::to<std::vector>(
        inputs | std::views::transform(List::FromString));
    auto expected_result = "1,1,2,3,4,4,5,6";
    auto heads = std::ranges::to<std::vector>(
        input_lists | std::views::transform(&List::head));
    auto actual_result = ListToString(Solution{}.mergeKLists(heads));
    ASSERT_EQ(actual_result, expected_result);
}
