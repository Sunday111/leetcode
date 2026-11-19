#include "1851_largest_color_value_in_a_directed_graph.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::largestPathValue;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abaca" [[0,1],[0,2],[2,3],[3,4]] 3

"a" [[0,0]] -1

"hhqhuqhqff" [[0,1],[0,2],[2,3],[3,4],[3,5],[5,6],[2,7],[6,7],[7,8],[3,8],[5,8],[8,9],[3,9],[6,9]] 3
)cases");

class t1851_largest_color_value_in_a_directed_graph
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1851_largest_color_value_in_a_directed_graph, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.largestPathValue(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1851_largest_color_value_in_a_directed_graph,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
