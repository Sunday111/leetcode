#include "3623_count_number_of_trapezoids_1.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3623_count_number_of_trapezoids_1, test_1)
{
    auto pts = parse2DArray("[[1,0],[2,0],[3,0],[2,2],[3,2]]");
    ASSERT_EQ(Solution{}.countTrapezoids(pts), 3);
}
