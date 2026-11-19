#include "0827_Making_A_Large_Island.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::largestIsland;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,0],[0,1]] 3

[[1,1],[1,1]] 4
)cases");

class t0827_Making_A_Large_Island : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0827_Making_A_Large_Island, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.largestIsland(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0827_Making_A_Large_Island,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
