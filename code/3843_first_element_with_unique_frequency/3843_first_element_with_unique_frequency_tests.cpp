#include "3843_first_element_with_unique_frequency.hpp"
#include "gtest/gtest.h"

TEST(t3843_first_element_with_unique_frequency, test_1)
{
    std::vector<int> nums{20, 10, 30, 30};
    ASSERT_EQ(Solution{}.firstUniqueFreq(nums), 30);
}

TEST(t3843_first_element_with_unique_frequency, test_2)
{
    std::vector<int> nums{20, 20, 10, 30, 30, 30};
    ASSERT_EQ(Solution{}.firstUniqueFreq(nums), 20);
}

TEST(t3843_first_element_with_unique_frequency, test_3)
{
    std::vector<int> nums{10, 10, 20, 20};
    ASSERT_EQ(Solution{}.firstUniqueFreq(nums), -1);
}
