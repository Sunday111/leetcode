#include "2147_number_of_ways_to_divide_a_long_corridor.hpp"
#include "gtest/gtest.h"

TEST(t2147_number_of_ways_to_divide_a_long_corridor, test_1)
{
    ASSERT_EQ(Solution{}.numberOfWays("SSPPSPS"), 3);
}

TEST(t2147_number_of_ways_to_divide_a_long_corridor, test_2)
{
    ASSERT_EQ(Solution{}.numberOfWays("PPSPSP"), 1);
}

TEST(t2147_number_of_ways_to_divide_a_long_corridor, test_3)
{
    ASSERT_EQ(Solution{}.numberOfWays("S"), 0);
}

TEST(t2147_number_of_ways_to_divide_a_long_corridor, test_4)
{
    ASSERT_EQ(Solution{}.numberOfWays("P"), 0);
}
