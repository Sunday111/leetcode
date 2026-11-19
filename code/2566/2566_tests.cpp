#include "2566.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minMaxDifference;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1001 9009
)cases");

using t2566 = SolutionTests<Solution>;

TEST_P(t2566, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minMaxDifference(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2566,
    t2566::parameters(kCases.size()),
    t2566::name);
