#include "1838_frequency_of_the_most_frequent_element.hpp"
#include "gtest/gtest.h"

TEST(t1838_frequency_of_the_most_frequent_element, test_1)
{
    std::vector nums{1, 4, 8, 13};
    ASSERT_EQ(Solution{}.maxFrequency(nums, 5), 2);
}
