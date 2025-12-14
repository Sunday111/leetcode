#include "1137_nth_tribonacci_number.hpp"
#include "gtest/gtest.h"

TEST(t1137_nth_tribonacci_number, test_1)
{
    ASSERT_EQ(Solution{}.tribonacci(4), 4);
    ASSERT_EQ(Solution{}.tribonacci(25), 1389537);
}
