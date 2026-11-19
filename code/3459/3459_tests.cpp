#include "3459.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lenOfVDiagonal;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]] 5

[[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]] 4

[[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]] 5

[[1]] 1

[[2,0],[0,1]] 2

[[1,2,0,0],[0,0,1,2]] 2
)cases");

using t3459 = SolutionTests<Solution>;

TEST_P(t3459, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lenOfVDiagonal(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3459,
    t3459::parameters(kCases.size()),
    t3459::name);
