#include "0059.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::generateMatrix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[1,2,3],[8,9,4],[7,6,5]]
)cases");

using t0059 = SolutionTests<Solution>;

TEST_P(t0059, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.generateMatrix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0059,
    t0059::parameters(kCases.size()),
    t0059::name);
