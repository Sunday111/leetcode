#include "0746_min_cost_climbing_stairs.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minCostClimbingStairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,15,20] 15

[1,100,1,1,1,100,1,1,100,1] 6
)cases");

class t0746_min_cost_climbing_stairs : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0746_min_cost_climbing_stairs, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minCostClimbingStairs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0746_min_cost_climbing_stairs,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
