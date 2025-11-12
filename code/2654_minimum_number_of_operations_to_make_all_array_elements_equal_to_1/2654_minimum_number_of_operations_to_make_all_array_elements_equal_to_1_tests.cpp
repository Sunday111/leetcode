#include "2654_minimum_number_of_operations_to_make_all_array_elements_equal_to_1.hpp"
#include "gtest/gtest.h"

TEST(
    t2654_minimum_number_of_operations_to_make_all_array_elements_equal_to_1,
    test_1)
{
    std::vector<int> nums{6, 10, 15};
    ASSERT_EQ(Solution{}.minOperations(nums), 4);
}

TEST(
    t2654_minimum_number_of_operations_to_make_all_array_elements_equal_to_1,
    test_2)
{
    std::vector<int> nums{2, 6, 3, 4};
    ASSERT_EQ(Solution{}.minOperations(nums), 4);
}
