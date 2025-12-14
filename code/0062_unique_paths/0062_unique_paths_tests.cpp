#include "0062_unique_paths.hpp"
#include "gtest/gtest.h"

TEST(t0062_unique_paths, test_1)
{
    ASSERT_EQ(Solution{}.uniquePaths(3, 7), 28);
    ASSERT_EQ(Solution{}.uniquePaths(3, 2), 3);
}
