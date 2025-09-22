#include "3346_maximum_frequency_of_an_element_after_performing_operations_i.hpp"
#include "gtest/gtest.h"

TEST(
    t3346_maximum_frequency_of_an_element_after_performing_operations_i,
    test_1)
{
    std::vector nums{5, 11, 20, 20};
    ASSERT_EQ(Solution{}.maxFrequency(nums, 5, 1), 2);
}

TEST(
    t3346_maximum_frequency_of_an_element_after_performing_operations_i,
    test_2)
{
    std::vector nums{88, 53};
    ASSERT_EQ(Solution{}.maxFrequency(nums, 27, 2), 2);
}
