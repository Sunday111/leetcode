#include "0072_edit_distance.hpp"
#include "gtest/gtest.h"

TEST(t0072_edit_distance, test_1)
{
    ASSERT_EQ(Solution{}.minDistance("horse", "ros"), 3);
}

TEST(t0072_edit_distance, test_2)
{
    ASSERT_EQ(Solution{}.minDistance("intention", "execution"), 5);
}

TEST(t0072_edit_distance, test_3)
{
    ASSERT_EQ(Solution{}.minDistance("", ""), 0);
}

TEST(t0072_edit_distance, test_4)
{
    ASSERT_EQ(Solution{}.minDistance("abc", "defghi"), 6);
}
TEST(t0072_edit_distance, test_5)
{
    ASSERT_EQ(Solution{}.minDistance("leet", "code"), 4);
}
TEST(t0072_edit_distance, test_6)
{
    ASSERT_EQ(
        Solution{}.minDistance("azertyqsdfghqwerty", "azertyjklmqwerty"),
        6);
}

TEST(t0072_edit_distance, test_7)
{
    ASSERT_EQ(
        Solution{}.minDistance("aaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaav"),
        8);
}

TEST(t0072_edit_distance, test_8)
{
    ASSERT_EQ(Solution{}.minDistance("aaayuio", "hjklaaa"), 7);
}

TEST(t0072_edit_distance, test_9)
{
    ASSERT_EQ(Solution{}.minDistance("sea", "eat"), 2);
}
