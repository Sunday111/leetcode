#include "3847_find_the_score_difference_in_a_game.hpp"
#include "gtest/gtest.h"

TEST(t3847_find_the_score_difference_in_a_game, test_1)
{
    std::vector nums{1, 2, 3};
    int expected = 0;
    int actual = Solution{}.scoreDifference(nums);
    ASSERT_EQ(expected, actual);
}

TEST(t3847_find_the_score_difference_in_a_game, test_2)
{
    std::vector nums{2, 4, 2, 1, 2, 1};
    int expected = 4;
    int actual = Solution{}.scoreDifference(nums);
    ASSERT_EQ(expected, actual);
}

TEST(t3847_find_the_score_difference_in_a_game, test_3)
{
    std::vector nums{1};
    int expected = -1;
    int actual = Solution{}.scoreDifference(nums);
    ASSERT_EQ(expected, actual);
}
