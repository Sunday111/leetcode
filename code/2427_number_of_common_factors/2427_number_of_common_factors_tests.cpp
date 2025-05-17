#include "2427_number_of_common_factors.hpp"
#include "gtest/gtest.h"

TEST(t2427_number_of_common_factors, test_1)
{
    EXPECT_EQ(Solution{}.commonFactors(12, 6), 4);
    EXPECT_EQ(Solution{}.commonFactors(25, 30), 2);
}
