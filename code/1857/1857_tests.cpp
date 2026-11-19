#include "1857.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::largestPathValue;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abaca" [[0,1],[0,2],[2,3],[3,4]] 3

"a" [[0,0]] -1

"hhqhuqhqff" [[0,1],[0,2],[2,3],[3,4],[3,5],[5,6],[2,7],[6,7],[7,8],[3,8],[5,8],[8,9],[3,9],[6,9]] 3
)cases");

using t1857 = SolutionTests<Solution>;

TEST_P(t1857, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestPathValue(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1857,
    t1857::parameters(kCases.size()),
    t1857::name);
