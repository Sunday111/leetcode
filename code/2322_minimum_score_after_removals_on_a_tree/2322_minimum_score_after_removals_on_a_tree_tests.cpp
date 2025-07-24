#include "2322_minimum_score_after_removals_on_a_tree.hpp"
#include "gtest/gtest.h"

TEST(t2322_minimum_score_after_removals_on_a_tree, test_1)
{
    std::vector<int> nums{5, 5, 2, 4, 4, 2};
    std::vector<std::vector<int>> edges{
        {0, 1},
        {1, 2},
        {5, 2},
        {4, 3},
        {1, 3},
    };
    ASSERT_EQ(Solution{}.minimumScore(nums, edges), 0);
}

TEST(t2322_minimum_score_after_removals_on_a_tree, test_2)
{
    std::vector<int> nums{1, 5, 5, 4, 11};
    std::vector<std::vector<int>> edges{
        {0, 1},
        {1, 2},
        {1, 3},
        {3, 4},
    };
    ASSERT_EQ(Solution{}.minimumScore(nums, edges), 9);
}
