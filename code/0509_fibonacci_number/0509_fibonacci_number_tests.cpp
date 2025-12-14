#include "0509_fibonacci_number.hpp"
#include "gtest/gtest.h"

TEST(t0509_fibonacci_number, test)
{
    ASSERT_EQ(Solution{}.fib(0), 0);
    ASSERT_EQ(Solution{}.fib(1), 1);
    ASSERT_EQ(Solution{}.fib(2), 1);
    ASSERT_EQ(Solution{}.fib(3), 2);
    ASSERT_EQ(Solution{}.fib(4), 3);
}
