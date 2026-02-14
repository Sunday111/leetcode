#include "0799_champagne_tower.hpp"
#include "gtest/gtest.h"

TEST(t0799_champagne_tower, test_1)
{
    ASSERT_NEAR(Solution{}.champagneTower(1, 1, 1), 0, 0.001);
    ASSERT_NEAR(Solution{}.champagneTower(2, 1, 1), 0.5, 0.001);
    ASSERT_NEAR(Solution{}.champagneTower(100000009, 33, 17), 1.0, 0.001);
}
