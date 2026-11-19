#include "3068_find_the_maximum_sum_of_node_values.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumValueSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[67,13,79,13,75,11,0,41,94] 7 [[0,1],[3,7],[4,7],[6,5],[6,0],[0,2],[7,2],[7,8]] 407
)cases");

class t3068_find_the_maximum_sum_of_node_values
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3068_find_the_maximum_sum_of_node_values, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maximumValueSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3068_find_the_maximum_sum_of_node_values,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
