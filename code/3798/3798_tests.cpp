#include "3798.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::largestEven;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1112" "1112"

"111" ""
)cases");

using t3798 = SolutionTests<Solution>;

TEST_P(t3798, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestEven(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3798,
    t3798::parameters(kCases.size()),
    t3798::name);
