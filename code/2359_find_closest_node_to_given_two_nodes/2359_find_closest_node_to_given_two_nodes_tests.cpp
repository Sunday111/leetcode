#include "2359_find_closest_node_to_given_two_nodes.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::closestMeetingNode;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[4,4,8,-1,9,8,4,4,1,1] 5 6 1
)cases");

using t2359_find_closest_node_to_given_two_nodes = SolutionTests<Solution>;

TEST_P(t2359_find_closest_node_to_given_two_nodes, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.closestMeetingNode(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2359_find_closest_node_to_given_two_nodes,
    t2359_find_closest_node_to_given_two_nodes::parameters(kCases.size()),
    t2359_find_closest_node_to_given_two_nodes::name);
