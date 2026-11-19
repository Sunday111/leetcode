#include "1733.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumTeachings;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[2],[1,3],[1,2],[3]] [[1,4],[1,2],[3,4],[2,3]] 2
)cases");

using t1733 = SolutionTests<Solution>;

TEST_P(t1733, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumTeachings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1733,
    t1733::parameters(kCases.size()),
    t1733::name);
