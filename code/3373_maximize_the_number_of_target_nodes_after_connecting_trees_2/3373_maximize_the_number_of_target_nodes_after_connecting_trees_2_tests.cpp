#include "3373_maximize_the_number_of_target_nodes_after_connecting_trees_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxTargetNodes;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,1],[0,2],[2,3],[2,4]] [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]] [8,7,7,8,8]

[[2,0],[4,1],[2,3],[2,4]] [[0,1],[0,2],[0,3]] [6,5,5,6,6]
)cases");

class t3373_maximize_the_number_of_target_nodes_after_connecting_trees_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3373_maximize_the_number_of_target_nodes_after_connecting_trees_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxTargetNodes(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3373_maximize_the_number_of_target_nodes_after_connecting_trees_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
