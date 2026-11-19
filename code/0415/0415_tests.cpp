#include "0415.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::addStrings;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"11" "123" "134"

"1" "9" "10"
)cases");

using t0415 = SolutionTests<Solution>;

TEST_P(t0415, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.addStrings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0415,
    t0415::parameters(kCases.size()),
    t0415::name);
