#include "1503_last_momemnt_before_all_ants_fall_out_of_a_plank.hpp"
#include "gtest/gtest.h"

TEST(t1503_last_momemnt_before_all_ants_fall_out_of_a_plank, test_1)
{
    Solution s{};
    int n = 4;
    std::vector left{4, 3};
    std::vector right{0, 1};
    int expected = 4;
    int actual = s.getLastMoment(n, left, right);
    ASSERT_EQ(expected, actual);
}
