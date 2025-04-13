#include "0238_product_of_array_except_self.hpp"
#include "gtest/gtest.h"

TEST(t0238_product_of_array_except_self, test_1)
{
    Solution s{};
    std::vector<int> input{1, 2, 3, 4};
    std::vector<int> expected{24, 12, 8, 6};
    EXPECT_EQ(s.productExceptSelf(input), expected);
}
