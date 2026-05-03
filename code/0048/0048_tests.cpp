#include "0048_test_cases.hpp"
#include "gtest/gtest.h"

class t0048 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0048, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution{}.rotate(inputs);
    ASSERT_EQ(expected, inputs);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0048,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
