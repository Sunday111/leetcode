#include "2434_using_a_robot_to_print_the_lexicographically_smallest_string.hpp"
#include "gtest/gtest.h"

TEST(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, test_1)
{
    ASSERT_EQ(Solution::robotWithString("zza"), "azz");
}

TEST(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, test_2)
{
    ASSERT_EQ(Solution::robotWithString("bac"), "abc");
}

TEST(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, test_3)
{
    ASSERT_EQ(Solution::robotWithString("bdda"), "addb");
}

TEST(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, test_4)
{
    ASSERT_EQ(Solution::robotWithString("bydizfve"), "bdevfziy");
}

TEST(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, test_5)
{
    ASSERT_EQ(Solution::robotWithString("bzeyxf"), "befxyz");
}

TEST(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, test_6)
{
    ASSERT_EQ(Solution::robotWithString("vzhofnpo"), "fnohopzv");
}

TEST(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, test_7)
{
    ASSERT_EQ(
        Solution::robotWithString("mmuqezwmomeplrtskz"),
        "eekstrlpmomwzqummz");
}
