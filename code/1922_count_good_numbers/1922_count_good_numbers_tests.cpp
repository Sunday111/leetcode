#include "1922_count_good_numbers.hpp"
#include "gtest/gtest.h"

TEST(t1922_count_good_numbers, test_1)
{
    EXPECT_EQ(Solution{}.countGoodNumbers(1), 5);
    EXPECT_EQ(Solution{}.countGoodNumbers(4), 400);
    EXPECT_EQ(Solution{}.countGoodNumbers(50), 564908303);
    EXPECT_EQ(Solution{}.countGoodNumbers(806166225460393), 643535977);
}
