#include "1201_ugly_number_3.hpp"
#include "gtest/gtest.h"

TEST(t1201_ugly_number_3, test_1)
{
    ASSERT_EQ(Solution{}.nthUglyNumber(3, 2, 3, 5), 4);
}

TEST(t1201_ugly_number_3, test_2)
{
    ASSERT_EQ(Solution{}.nthUglyNumber(4, 2, 3, 4), 6);
}

TEST(t1201_ugly_number_3, test_3)
{
    ASSERT_EQ(Solution{}.nthUglyNumber(5, 2, 11, 13), 10);
}

TEST(t1201_ugly_number_3, test_4)
{
    ASSERT_EQ(
        Solution{}.nthUglyNumber(1000000000, 2, 740091218, 473796308),
        2000000000);
}
