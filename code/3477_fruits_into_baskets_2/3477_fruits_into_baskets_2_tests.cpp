#include "3477_fruits_into_baskets_2.hpp"
#include "gtest/gtest.h"

TEST(t3477_fruits_into_baskets_2, test_1)
{
    std::vector baskets{3, 6, 1};
    std::vector fruits{6, 4, 7};
    ASSERT_EQ(Solution{}.numOfUnplacedFruits(baskets, fruits), 0);
}
