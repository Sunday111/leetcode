#include "2509.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::cycleLengthQueries;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 [[1,2]] [2]

3 [[5,3],[4,7],[2,3]] [4,5,3]

5 [[17,21],[23,5],[15,7],[3,21],[31,9],[5,15],[11,2],[19,7]] [7,3,2,6,8,6,3,7]
)cases");

using t2509 = SolutionTests<Solution>;

TEST_P(t2509, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.cycleLengthQueries(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2509,
    t2509::parameters(kCases.size()),
    t2509::name);
