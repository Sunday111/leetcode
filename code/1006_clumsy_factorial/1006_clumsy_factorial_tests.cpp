#include "1006_clumsy_factorial.hpp"
#include "gtest/gtest.h"

TEST(t1006_clumsy_factorial, test_1)
{
    ASSERT_EQ(Solution{}.clumsy(4), 7);
}

TEST(t1006_clumsy_factorial, test_2)
{
    ASSERT_EQ(Solution{}.clumsy(10), 12);
}
