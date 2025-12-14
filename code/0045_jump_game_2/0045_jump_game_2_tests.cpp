#include "0045_jump_game_2.hpp"
#include "gtest/gtest.h"

TEST(t0045_jump_game_2, test_1)
{
    std::vector nums{2, 3, 1, 1, 4};
    ASSERT_EQ(Solution{}.jump(nums), 2);
}

TEST(t0045_jump_game_2, test_2)
{
    std::vector nums{2, 3, 0, 1, 4};
    ASSERT_EQ(Solution{}.jump(nums), 2);
}

TEST(t0045_jump_game_2, test_3)
{
    std::vector nums{0};
    ASSERT_EQ(Solution{}.jump(nums), 0);
}
