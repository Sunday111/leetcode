#include "1751_maximum_number_of_events_that_can_be_attended_2.hpp"
#include "gtest/gtest.h"

TEST(t1751_maximum_number_of_events_that_can_be_attended_2, test_1)
{
    std::vector<std::vector<int>> events{
        {1, 2, 4},
        {3, 4, 3},
        {2, 3, 1},
    };
    ASSERT_EQ(Solution::maxValue(events, 2), 7);
}

TEST(t1751_maximum_number_of_events_that_can_be_attended_2, test_2)
{
    std::vector<std::vector<int>> events{
        {1, 2, 4},
        {3, 4, 3},
        {2, 3, 10},
    };
    ASSERT_EQ(Solution::maxValue(events, 2), 10);
}

TEST(t1751_maximum_number_of_events_that_can_be_attended_2, test_3)
{
    std::vector<std::vector<int>> events{
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3},
        {4, 4, 4},
    };
    ASSERT_EQ(Solution::maxValue(events, 3), 9);
}
