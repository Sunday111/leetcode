#include "3275_kth_nearest_obstacle.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3275_kth_nearest_obstacle, test_1)
{
    auto q = parse2DArray("[[1,2],[3,4],[2,3],[-3,0]]");
    const std::vector expected{-1, 7, 5, 3};
    ASSERT_EQ(Solution{}.resultsArray(q, 2), expected);
}
