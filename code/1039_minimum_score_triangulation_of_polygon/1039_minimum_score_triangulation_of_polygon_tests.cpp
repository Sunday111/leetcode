#include "1039_minimum_score_triangulation_of_polygon.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minScoreTriangulation;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,3,1,4,1,5] 13
)cases");

using t1039_minimum_score_triangulation_of_polygon = SolutionTests<Solution>;

TEST_P(t1039_minimum_score_triangulation_of_polygon, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minScoreTriangulation(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1039_minimum_score_triangulation_of_polygon,
    t1039_minimum_score_triangulation_of_polygon::parameters(kCases.size()),
    t1039_minimum_score_triangulation_of_polygon::name);
