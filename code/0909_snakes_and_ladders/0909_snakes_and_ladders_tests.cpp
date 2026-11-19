#include "0909_snakes_and_ladders.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::snakesAndLadders;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
4

[[-1,-1,-1],[-1,9,8],[-1,8,9]] 1
)cases");

class t0909_snakes_and_ladders : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0909_snakes_and_ladders, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.snakesAndLadders(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0909_snakes_and_ladders,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
