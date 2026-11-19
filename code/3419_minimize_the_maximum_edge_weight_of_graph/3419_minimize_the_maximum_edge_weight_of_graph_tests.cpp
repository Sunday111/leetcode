#include "3419_minimize_the_maximum_edge_weight_of_graph.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minMaxWeight;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 [[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]] 2 1
)cases");

class t3419_minimize_the_maximum_edge_weight_of_graph
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3419_minimize_the_maximum_edge_weight_of_graph, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minMaxWeight(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3419_minimize_the_maximum_edge_weight_of_graph,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
