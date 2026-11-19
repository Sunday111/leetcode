#include "1292.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSideLength;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]] 4 2
)cases");

using t1292 = SolutionTests<Solution>;

TEST_P(t1292, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSideLength(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1292,
    t1292::parameters(kCases.size()),
    t1292::name);
