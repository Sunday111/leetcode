#include "0052_n_queens_2.hpp"
#include "gtest/gtest.h"

TEST(t0052_n_queens_2, test_1)
{
    ASSERT_EQ(Solution{}.totalNQueens(4), 2);
}
