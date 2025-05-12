#include "0016_3sum_closest.hpp"
#include "gtest/gtest.h"

TEST(t0016_3sum_closest, test_1)
{
    std::vector input{-1, 2, 1, -4};
    ASSERT_EQ(Solution{}.threeSumClosest(input, 1), 2);
}

TEST(t0016_3sum_closest, test_2)
{
    std::vector input{0, 0, 0};
    ASSERT_EQ(Solution{}.threeSumClosest(input, 1), 0);
}

TEST(t0016_3sum_closest, test_3)
{
    std::vector input{1, 5, 6, 7, 8};
    ASSERT_EQ(Solution{}.threeSumClosest(input, 10), 12);
}

TEST(t0016_3sum_closest, test_4)
{
    std::vector input{2, 3, 8, 9, 10};
    ASSERT_EQ(Solution{}.threeSumClosest(input, 16), 15);
}

TEST(t0016_3sum_closest, test_5)
{
    std::vector input{-1000, -5, -5, -5, -1};
    ASSERT_EQ(Solution{}.threeSumClosest(input, -14), -15);
}

TEST(t0016_3sum_closest, test_6)
{
    std::vector input{-2, -1, 1, 4};
    ASSERT_EQ(Solution{}.threeSumClosest(input, 0), 1);
}

TEST(t0016_3sum_closest, test_7)
{
    std::vector input{0, 1, 2};
    ASSERT_EQ(Solution{}.threeSumClosest(input, 3), 3);
}

TEST(t0016_3sum_closest, test_8)
{
    std::vector input{0, 3, 97, 102, 200};
    ASSERT_EQ(Solution{}.threeSumClosest(input, 300), 300);
}
