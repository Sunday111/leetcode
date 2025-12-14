#include "0055_jump_game.hpp"
#include "gtest/gtest.h"

TEST(t0055_jump_game, test_1)
{
    std::vector nums{2, 3, 1, 1, 4};
    ASSERT_EQ(Solution{}.canJump(nums), true);
}

TEST(t0055_jump_game, test_2)
{
    std::vector nums{3, 2, 1, 0, 4};
    ASSERT_EQ(Solution{}.canJump(nums), false);
}
