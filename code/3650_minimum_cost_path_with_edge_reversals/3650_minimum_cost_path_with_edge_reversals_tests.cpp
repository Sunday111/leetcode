#include "3650_minimum_cost_path_with_edge_reversals.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minCost;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 [[0,1,3],[3,1,1],[2,3,4],[0,2,2]] 5

4 [[0,2,1],[2,1,1],[1,3,1],[2,3,3]] 3

4 [[2,3,25],[2,1,18],[3,1,2]] -1
)cases");

class t3650_minimum_cost_path_with_edge_reversals
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3650_minimum_cost_path_with_edge_reversals, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minCost(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3650_minimum_cost_path_with_edge_reversals,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
