#include "2528_maximize_the_minimum_powered_city.hpp"
#include "gtest/gtest.h"

TEST(t2528_maximize_the_minimum_powered_city, test_1)
{
    std::vector stations{4, 4, 4, 4};
    u32 r = 0, k = 3;
    ASSERT_EQ(Solution{}.maxPower(stations, r, k), 4);
}
