#include "0837_new_game.hpp"
#include "gtest/gtest.h"

TEST(t0837_new_game, test_1)
{
    ASSERT_FLOAT_EQ(Solution{}.new21Game(10, 1, 10), 1.f);
}

TEST(t0837_new_game, test_2)
{
    ASSERT_FLOAT_EQ(Solution{}.new21Game(1, 0, 1), 1.f);
}
