#include "3202.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumLength;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4,5] 2 5

[1,9,3,10,10] 4 2
)cases");

using t3202 = SolutionTests<Solution>;

TEST_P(t3202, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumLength(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3202,
    t3202::parameters(kCases.size()),
    t3202::name);
