#include "1411_num_of_ways.hpp"
#include "gtest/gtest.h"

TEST(t1411_num_of_ways, test_1)
{
    ASSERT_EQ(Solution{}.numOfWays(1), 12);
    ASSERT_EQ(Solution{}.numOfWays(5000), 30228214);
}
