#include "2359_find_closest_node_to_given_two_nodes.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::closestMeetingNode;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[4,4,8,-1,9,8,4,4,1,1] 5 6 1
)cases");

class t2359_find_closest_node_to_given_two_nodes
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2359_find_closest_node_to_given_two_nodes, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.closestMeetingNode(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2359_find_closest_node_to_given_two_nodes,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
