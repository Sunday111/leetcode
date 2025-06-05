#include "1404_number_of_steps_to_reduce_a_number_to_one.hpp"
#include "gtest/gtest.h"

TEST(t1404_number_of_steps_to_reduce_a_number_to_one, test_1)
{
    EXPECT_EQ(Solution{}.numSteps("1101"), 6);
    EXPECT_EQ(Solution{}.numSteps("11000"), 6);
    EXPECT_EQ(Solution{}.numSteps("10"), 1);
}
