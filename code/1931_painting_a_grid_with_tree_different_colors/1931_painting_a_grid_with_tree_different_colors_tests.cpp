#include "1931_painting_a_grid_with_tree_different_colors.hpp"
#include "gtest/gtest.h"

TEST(t1931_painting_a_grid_with_tree_different_colors, test_1)
{
    ASSERT_EQ(Solution{}.colorTheGrid(3, 1), 12);
    ASSERT_EQ(Solution{}.colorTheGrid(3, 2), 54);
    ASSERT_EQ(Solution{}.colorTheGrid(3, 3), 246);
}
