
#include "0029_divide_two_integers.hpp"
#include "0029_divide_two_integers_msb.hpp"
#include "gtest/gtest.h"
#include "random_data.hpp"

TEST(t0029_divide_two_integers_tests, msb)
{
    for (auto [a, b] : RandomData::Instance().values)
    {
        ASSERT_EQ(Solution::divide(a, b), SolutionMSB::divide(a, b));
    }
}
