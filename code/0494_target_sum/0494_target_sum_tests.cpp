#include "0494_target_sum.hpp"
#include "gtest/gtest.h"

TEST(t0494_target_sum, test_1)
{
    Solution s{};
    std::vector<int32_t> input{1, 1, 1, 1, 1};
    constexpr int32_t target = 3;
    constexpr int32_t expected = 5;
    ASSERT_EQ(s.findTargetSumWays(input, target), expected);
}
