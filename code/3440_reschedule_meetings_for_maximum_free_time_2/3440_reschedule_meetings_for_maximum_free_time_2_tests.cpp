#include "3440_reschedule_meetings_for_maximum_free_time_2.hpp"
#include "gtest/gtest.h"

TEST(t3440_reschedule_meetings_for_maximum_free_time_2, test_1)
{
    std::vector<int> start{1, 3};
    std::vector<int> finish{2, 5};
    ASSERT_EQ(Solution::maxFreeTime(5, start, finish), 2);
}

TEST(t3440_reschedule_meetings_for_maximum_free_time_2, test_2)
{
    std::vector<int> start{5, 14, 27, 34};
    std::vector<int> finish{13, 18, 31, 37};
    ASSERT_EQ(Solution::maxFreeTime(37, start, finish), 16);
}

TEST(t3440_reschedule_meetings_for_maximum_free_time_2, test_3)
{
    std::vector<int> start{2, 4, 6, 9, 18};
    std::vector<int> finish{4, 6, 9, 16, 20};
    ASSERT_EQ(Solution::maxFreeTime(20, start, finish), 4);
}
