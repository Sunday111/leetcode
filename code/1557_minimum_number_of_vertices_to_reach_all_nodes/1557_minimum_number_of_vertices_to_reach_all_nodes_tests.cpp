#include "1557_minimum_number_of_vertices_to_reach_all_nodestest_cases.hpp"
#include "solution_tests.hpp"

using t1557_minimum_number_of_vertices_to_reach_all_nodes =
    SolutionTests<Solution>;

TEST_P(t1557_minimum_number_of_vertices_to_reach_all_nodes, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findSmallestSetOfVertices(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1557_minimum_number_of_vertices_to_reach_all_nodes,
    t1557_minimum_number_of_vertices_to_reach_all_nodes::parameters(
        kCases.size()),
    t1557_minimum_number_of_vertices_to_reach_all_nodes::name);
