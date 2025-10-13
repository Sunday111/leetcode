#include "3625_count_number_of_trapezoids_2.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3625_count_number_of_trapezoids_2, test_1)
{
    auto pts = parse2DArray("[[0,0],[1,0],[0,1],[2,1]]");
    ASSERT_EQ(Solution{}.countTrapezoids(pts), 1);
}

TEST(t3625_count_number_of_trapezoids_2, test_2)
{
    auto pts = parse2DArray("[[-3,2],[3,0],[2,3],[3,2],[2,-3]]");
    ASSERT_EQ(Solution{}.countTrapezoids(pts), 2);
}

TEST(t3625_count_number_of_trapezoids_2, test_3)
{
    auto pts = parse2DArray(
        "[[71,-89],[-75,-89],[-9,11],[-24,-89],[-51,-89],[-77,-89],[42,11]]");
    ASSERT_EQ(Solution{}.countTrapezoids(pts), 10);
}
