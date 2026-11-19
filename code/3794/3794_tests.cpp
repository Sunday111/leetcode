#include "3794.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reversePrefix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcd" 2 "bacd"
)cases");

using t3794 = SolutionTests<Solution>;

TEST_P(t3794, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.reversePrefix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3794,
    t3794::parameters(kCases.size()),
    t3794::name);
