#include "3727_minimum_alternating_sum_of_squares.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxAlternatingSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 12

[1,-1,2,-2,3,-3] 16
)cases");

class t3727_minimum_alternating_sum_of_squares
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3727_minimum_alternating_sum_of_squares, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxAlternatingSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3727_minimum_alternating_sum_of_squares,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
