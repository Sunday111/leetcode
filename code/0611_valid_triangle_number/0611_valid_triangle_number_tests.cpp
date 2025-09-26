#include "0611_valid_triangle_number.hpp"
#include "gtest/gtest.h"

TEST(t0611_valid_triangle_number, test_1)
{
    std::vector<int> nums{2, 2, 3, 4};
    ASSERT_EQ(Solution{}.triangleNumber(nums), 3);
}
TEST(t0611_valid_triangle_number, test_2)
{
    std::vector<int> nums{1, 1, 3, 4};
    ASSERT_EQ(Solution{}.triangleNumber(nums), 0);
}
TEST(t0611_valid_triangle_number, test_3)
{
    std::vector<int> nums{0, 2, 2};
    ASSERT_EQ(Solution{}.triangleNumber(nums), 0);
}
TEST(t0611_valid_triangle_number, test_4)
{
    std::vector<int> nums{2, 3, 4, 4};
    ASSERT_EQ(Solution{}.triangleNumber(nums), 4);
}
