#include "0494_target_sum.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findTargetSumWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,1] 3 5
)cases");

class t0494_target_sum : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0494_target_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.findTargetSumWays(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0494_target_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
