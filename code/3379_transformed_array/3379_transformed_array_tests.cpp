#include "3379_transformed_array.hpp"
#include "gtest/gtest.h"

TEST(t3379_transformed_array, test_1)
{
    std::vector nums{3, -2, 1, 1};
    std::vector expected{1, 1, 1, 3};
    auto actual = Solution{}.constructTransformedArray(nums);
    ASSERT_EQ(expected, actual);
}
