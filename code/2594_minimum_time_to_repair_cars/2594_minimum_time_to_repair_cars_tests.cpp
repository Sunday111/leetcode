#include "2594_minimum_time_to_repair_cars.hpp"
#include "gtest/gtest.h"

TEST(t2594_minimum_time_to_repair_cars, test_1)
{
    std::vector<int> ranks{1, 2, 3, 4};
    ASSERT_EQ(Solution{}.repairCars(ranks, 10), 16);
}
