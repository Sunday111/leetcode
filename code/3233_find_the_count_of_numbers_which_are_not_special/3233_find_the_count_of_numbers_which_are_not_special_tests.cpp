#include "3233_find_the_count_of_numbers_which_are_not_special.hpp"
#include "gtest/gtest.h"

TEST(t3233_find_the_count_of_numbers_which_are_not_special, test_1)
{
    ASSERT_EQ(Solution{}.nonSpecialCount(5, 7), 3);
}

TEST(t3233_find_the_count_of_numbers_which_are_not_special, test_2)
{
    ASSERT_EQ(Solution{}.nonSpecialCount(4, 16), 11);
}

TEST(t3233_find_the_count_of_numbers_which_are_not_special, test_3)
{
    ASSERT_EQ(Solution{}.nonSpecialCount(1, 100'000), 99935);
}

TEST(t3233_find_the_count_of_numbers_which_are_not_special, test_4)
{
    ASSERT_EQ(Solution{}.nonSpecialCount(1, 4), 3);
}
